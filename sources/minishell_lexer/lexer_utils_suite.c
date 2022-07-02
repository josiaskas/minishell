/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils_suite.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkasongo <jkasongo@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 16:34:24 by jkasongo          #+#    #+#             */
/*   Updated: 2022/06/25 16:34:28 by jkasongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"
#include "../../includes/minishell.h"

/*
 * return true if token is a redirection token
 */
bool	is_minishell_redir(t_token *token)
{
	if (token)
	{
		if ((token->type == e_token_less)
			|| (token->type == e_token_greater)
			|| (token->type == e_token_heredoc_right)
			|| (token->type == e_token_heredoc_left)
			|| (token->type == e_token_herestr))
			return (true);
	}
	return (false);
}

/*
 * return the g_shell.satus, but can be reset to 0
 * 128 to reset every call after that return 0
 * 1 to reset return to real g_shell.status after that call
 * other number to not influence
 */
int	lex_get_status_value(int is_reset)
{
	static int	is_to_zero = 0;
	int			value;

	value = 0;
	if (is_reset == 128)
		is_to_zero = 1;
	else if (is_reset == 1)
		is_to_zero = 0;
	if (is_to_zero == 1)
		value = 0;
	else
		value = g_shell.status;
	return (value);
}

void	destroy_lexer(t_array *lexer)
{
	t_lex_token	*content;

	if (!lexer)
		return ;
	while (lexer->length)
	{
		content = (t_lex_token *)ft_pop(lexer);
		free(content->value);
		free(content);
	}
	free(lexer);
	lexer = NULL;
}

bool	check_if_is_literal(t_token *tok)
{
	if ((tok->type != e_token_space)
		&& (!is_minishell_redir(tok))
		&& (tok->type != e_token_pipe)
		&& (tok->type != e_token_or)
		&& (tok->type != e_token_eof))
	{
		return (true);
	}
	return (false);
}

/*
 * Check if a token is repeated, closed.
 * go from cursor to eof if not return false
 */
bool	is_close_t_s(t_array *tokens, t_token *token, size_t i)
{
	t_token_type	closing_type;

	if (token->type == e_token_left_paren)
		closing_type = e_token_right_paren;
	else
		closing_type = token->type;
	if (token->type == e_token_eof)
		return (false);
	if (token->type == e_token_right_paren)
		return (false);
	token = (t_token *)ft_get_elem(tokens, ++i);
	while ((token->type != closing_type) && (token->type != e_token_eof))
	{
		token = (t_token *)ft_get_elem(tokens, ++i);
	}
	if (token->type == e_token_eof)
		return (false);
	return(true);
}