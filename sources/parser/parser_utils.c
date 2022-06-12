/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkasongo <jkasongo@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 01:09:34 by jkasongo          #+#    #+#             */
/*   Updated: 2022/06/10 18:38:47 by jkasongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

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

	if (!command)
		return ;
	list = "echo cd pwd export unset env exit";
	internals = ft_split(list, ' ');
	i = 0;
	while (internals[i] != NULL)
	{
		if (!ft_strncmp(command->cmd, internals[i], ft_strlen(command->cmd)))
		{
			command->is_internal = true;
			command->internal_cmd = i;
		}
		i++;
	}
}

/*
 * Check parse errors and errors to parser
 * return boolean (true) if no error (false) if found errors;
 */
bool	check_p_err(t_array *lex, t_shell *parser, size_t i)
{
	t_lex_token	*token;
	char		*error_msg;

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
			error_msg = "syntax error near unexpected token";
			if (token->type == e_lex_pipe_error)
				error_msg = "syntax error near unexpected token `|'";
			else if (token->type == e_lex_redirection_error)
				error_msg = "syntax error near unexpected token `<'";
			else if (token->type == e_lex_quote_error)
				error_msg = "syntax error Quote error";
			free(parser->error_msg);
			parser->error_msg = ft_strdup(error_msg);
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
