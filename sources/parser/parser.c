/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkasongo <jkasongo@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 00:24:38 by jkasongo          #+#    #+#             */
/*   Updated: 2022/05/04 21:33:27 by jkasongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

/*
 * Add cmd name or arguments to array of args inside t_command cmd
 * Return void
 */
void    build_cmd_args(t_lex_token *tok, t_command *cmd)
{

    if (!tok)
    {
        cmd->state = e_cmd_error;
        return ;
    }
    if (!cmd->cmd)
    {
        cmd->cmd = ft_strdup(tok->value);
        check_internal_cmd(cmd);
    }
    else
    {
        if (!cmd->arguments)
            cmd->arguments = ft_new_array();
        ft_push(cmd->arguments, ft_strdup(tok->value));
    }
}

/*
 * Build cmd->redirections array if not already built.
 * Add a redirection inside cmd->redirections
 * by catching next lexical literal as filename
 * Return void
 */
size_t  build_red(t_lex_token *tok, t_command *cmd, size_t i, t_array *lex)
{
    t_redirection   *redirection;

    if (!tok)
    {
        cmd->state = e_cmd_error;
        return (i);
    }
    if (!cmd->redirections)
        cmd->redirections = ft_new_array();
    redirection = (t_redirection *)ft_calloc(1, sizeof(t_redirection));
    redirection->type = tok->r_type;
    redirection->fd = tok->fd;
    redirection->filename = get_red_filename(i, lex);
    if (!redirection->filename)
        cmd->state = e_cmd_error;
    ft_push(cmd->redirections, redirection);
    return (i + 1);
}

/*
 * Build a t_command from lexer array of tokens
 */
t_command   *build_cmd(t_array *lexer, size_t cursor)
{
    t_command   *cmd;
    t_lex_token *token;

    cmd = (t_command *)ft_calloc(1, sizeof(t_command));
    while (cursor < lexer->length)
    {
        token = (t_lex_token *)ft_get_elem(lexer, cursor);
        if (token->type == e_lex_literal)
            build_cmd_args(token, cmd);
        else if (token->type == e_lex_redirection)
            cursor = build_red(token, cmd, cursor, lexer);
        else if (token->type == e_lex_pipe)
        {
            cmd->next = build_cmd(lexer, ++cursor);
            cursor = cmd->next->cursor;
            if ((cmd->next->state == e_cmd_error) || (!cmd->next->cmd))
                cmd->state = e_cmd_error;
        }
        if (cmd->state == e_cmd_error)
            break;
        cursor++;
    }
    cmd->cursor = cursor;
    return (cmd);
}

int	parse_line(char *sentence)
{
	t_tokeniser *lexical_anyliser;
	t_token     *token;
    t_array     *lexer;
    t_command   *commands;

	lexical_anyliser = init_tokenizer(sentence);
	token = get_next_token(lexical_anyliser);
	while (token->type != e_token_eof)
		token = get_next_token(lexical_anyliser);
    lexer = run_simple_lexer(lexical_anyliser->tokens);
    if (check_parse_errors(lexer))
    {
        commands = build_cmd(lexer, 0);
        ft_print_cmd(commands);
    }
    destroy_lexer(lexer);
	destroy_tokinizer(lexical_anyliser);
	return (0);
}
