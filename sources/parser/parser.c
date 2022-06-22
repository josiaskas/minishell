/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkasongo <jkasongo@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 00:24:38 by jkasongo          #+#    #+#             */
/*   Updated: 2022/06/22 18:20:20 by jkasongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"
#include "../../includes/minishell.h"

/*
 * Add cmd name or arguments to array of args inside t_command cmd
 * Return void
 */
static void	build_cmd_args(t_lex_token *tok, t_command *cmd)
{
	if (!cmd->cmd)
	{
		if (tok->value)
		{
			cmd->cmd = ft_strdup(tok->value);
			check_internal_cmd(cmd);
		}
	}
	else
	{
		if (!cmd->arguments)
			cmd->arguments = ft_new_array();
		if (tok->value)
			ft_push(cmd->arguments, ft_strdup(tok->value));
	}
}

/*
 * Build cmd->redirections array if not already built.
 * Add a redirection inside cmd->redirections
 * by catching next lexical literal as filename
 * Return void
 */
static size_t	b_re(t_lex_token *tok, t_command *cmd, size_t i, t_array *lex)
{
	t_redirection	*redirection;

	if (!cmd->redirections)
		cmd->redirections = ft_new_array();
	redirection = (t_redirection *)ft_calloc(1, sizeof(t_redirection));
	redirection->type = tok->r_type;
	redirection->fd = tok->fd;
	redirection->filename = get_red_filename(i, lex, cmd);
	ft_push(cmd->redirections, redirection);
	return (i + 1);
}

/*
 * Build a t_command from lexer array of tokens
 * if error t_commands->state == e_cmd_error
 */
t_command	*build_parse_cmd(t_array *lexer, size_t cursor)
{
	t_command	*cmd;
	t_lex_token	*token;

	cmd = (t_command *)ft_calloc(1, sizeof(t_command));
	cmd->state = e_cmd_waiting;
	cmd->error_msg = NULL;
	cmd->env = g_shell.env;
	while (cursor < lexer->length)
	{
		token = (t_lex_token *)ft_get_elem(lexer, cursor);
		if (token->type == e_lex_literal)
			build_cmd_args(token, cmd);
		else if (token->type == e_lex_redirection)
			cursor = b_re(token, cmd, cursor, lexer);
		else if (token->type == e_lex_pipe)
			cursor = build_pipe_cmd(cmd, lexer, cursor);
		if (cmd->state == e_cmd_error)
			break ;
		cursor++;
	}
	cmd->cursor = cursor;
	return (cmd);
}

/*
 * Build the lexical analyzer, and return array of t_lex_token
 */
static t_array	*build_lexical_analyser(char *sentence)
{
	t_tokeniser	*tokenizer;
	t_token		*token;
	t_array		*lexer;

	tokenizer = init_tokenizer(sentence);
	token = get_next_token(tokenizer);
	while (token->type != e_token_eof)
		token = get_next_token(tokenizer);
	lexer = run_simple_lexer(tokenizer->tokens);
	destroy_tokinizer(tokenizer);
	return (lexer);
}

t_shell	*parse_shell_line(char *sentence)
{
	t_array			*lexer;
	t_shell			*shell;

	shell = ft_calloc(1, sizeof(t_shell));
	shell->commands_list = NULL;
	shell->syntax_error = true;
	shell->error_msg = ft_strdup(
			"syntax error near unexpected token `newline'");
	lexer = build_lexical_analyser(sentence);
	if (check_p_err(lexer, shell, 0, NULL))
	{
		shell->commands_list = build_parse_cmd(lexer, 0);
		if (shell->commands_list->state == e_cmd_error)
		{
			if (shell->commands_list->error_msg)
				shell->error_msg = ft_strdup(shell->commands_list->error_msg);
			shell->status = 258;
		}
		else
			shell->syntax_error = false;
	}
	destroy_lexer(lexer);
	return (shell);
}
