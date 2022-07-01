/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkasongo <jkasongo@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 01:09:34 by jkasongo          #+#    #+#             */
/*   Updated: 2022/06/20 17:35:56 by jkasongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"
#include "../../includes/minishell.h"

/*
 * Check if the command is an internal command
 * set command->is_internal
 * set command->internal_cmd value
 */
void	check_internal_cmd(t_command *command)
{
	char	*list;
	char	**internals;
	int		i;
	size_t	len;

	if (!command)
		return ;
	list = "echo cd pwd export unset env exit";
	internals = ft_split(list, ' ');
	i = 0;
	while (internals[i] != NULL)
	{
		len = ft_strlen(command->cmd);
		if ((len == ft_strlen(internals[i]))
			&& (ft_strncmp(command->cmd, internals[i], len) == 0))
		{
			command->is_internal = true;
			command->internal_cmd = i;
		}
		i++;
	}
	ft_free_splitted(internals);
}

/*
 * Check parse errors and errors to parser
 * return boolean (true) if no error (false) if found errors;
 */
bool	check_p_err(t_array *lex, t_shell *parser, size_t i, char *msg)
{
	t_lex_token	*token;

	if (!lex || !parser)
		return (false);
	while (i < lex->length)
	{
		token = (t_lex_token *)ft_get_elem(lex, i++);
		if ((token->type == e_lex_pipe_error)
			|| (token->type == e_lex_redirection_error)
			|| (token->type == e_lex_quote_error))
		{
			parser->syntax_error = true;
			msg = "syntax error near unexpected token";
			if (token->type == e_lex_pipe_error)
				msg = "syntax error near unexpected token `|'";
			else if (token->type == e_lex_redirection_error)
				msg = "syntax error near unexpected token `<'";
			else if (token->type == e_lex_quote_error)
				msg = "syntax error Quote error";
			free(parser->error_msg);
			parser->error_msg = ft_strdup(msg);
			return (false);
		}
	}
	return (true);
}

/*
 * Get the filename for redirection
 * if error set cmd->error_msg
 */
char	*get_red_filename(size_t cursor, t_array *lexer, t_command *cmd)
{
	t_lex_token	*next_token;
	char		*filename;

	filename = NULL;
	next_token = (t_lex_token *)ft_get_elem(lexer, cursor + 1);
	if ((!next_token) || (next_token->type != e_lex_literal))
	{
		cmd->state = e_cmd_error;
		cmd->error_msg = ft_strdup("syntax error unexpected token");
		return (NULL);
	}
	if (next_token->value)
		filename = ft_strdup(next_token->value);
	return (filename);
}

/*
 * Make the pipe and if error during pipe parsing error is pushed forward
 * Check if token->type is e_lex_pipe
 * Change cmd state to error if no redirection or cmd name found
 * Return cursor
 */
size_t	build_pipe_cmd(t_command *cmd, t_array *lexer, size_t cursor)
{
	t_lex_token	*token;

	if ((!cmd->cmd) && (!cmd->redirections))
	{
		cmd->state = e_cmd_error;
		cmd->error_msg = ft_strdup("syntax error near unexpected token `|'");
		cursor++;
	}
	else
	{
		token = (t_lex_token *)ft_get_elem(lexer, cursor);
		if (token->type == e_lex_pipe)
		{
			cmd->pipe = build_parse_cmd(lexer, ++cursor);
			cursor = cmd->pipe->cursor;
			if ((cmd->pipe->state == e_cmd_error) || (!cmd->pipe->cmd))
			{
				cmd->state = e_cmd_error;
				cmd->error_msg = ft_strdup(cmd->pipe->error_msg);
			}
		}
	}
	return (cursor);
}

/*
 * This function update $_ to the last expended litteral
 * it can be the cmd->name or an arg of a command
 */
void	parser_update_special_underscore_var(char *value)
{
	t_dic_node	*dic;

	dic = NULL;
	dic = ft_elem_dic(g_shell.env, "_");
	if (dic)
	{
		free(dic->content);
		dic->content = value;
	}
	else
		ft_push_to_dic(g_shell.env, ft_strdup("_"), value);
}
