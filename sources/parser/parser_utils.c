/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkasongo <jkasongo@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 01:09:34 by jkasongo          #+#    #+#             */
/*   Updated: 2022/05/04 21:26:04 by jkasongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	ft_print_token(void *data, int index)
{
	t_token *token;

	(void)index;
	token = (t_token *)data;
	if ((token->type == e_token_text) || (token->type == e_token_space))
		ft_putstr_fd(token->value, STDOUT_FILENO);
	else if (token->type == e_token_eof)
		ft_putstr_fd("\033[0;31mEOF\033[0;39m", STDOUT_FILENO);
	else if ((token->type == e_token_subst) || (token->type == e_token_or) || (token->type == e_token_double_and) || (token->type == e_token_semicolon))
		ft_printf("\033[0;31m%s\033[0;39m", token->value);
	else if ((token->type == e_token_quote) || (token->type == e_token_dquote))
		ft_printf("\033[0;32m%s\033[0;39m", token->value);
	else if ((token->type == e_token_dollar) || (token->type == e_token_wildcard) || (token->type == e_token_number) || (token->type == e_token_tilde))
		ft_printf("\033[0;35m%s\033[0;39m", token->value);
	else
		ft_printf("\033[0;33m%s\033[0;39m", token->value);
}

void	ft_print_lex(void *data, int index)
{
    t_lex_token *token;

    (void)index;
    token = (t_lex_token *)data;
    if (token->type == e_lex_literal)
        ft_printf(" -literal: -(%s)- ", token->value);
    else if (token->type == e_lex_redirection)
    {
        ft_putstr_fd("\033[0;31m - redirection -\033[0;39m", STDOUT_FILENO);
    }
    else if (token->type == e_lex_quote_error)
    {
        ft_putstr_fd("\033[0;31m quote Error\033[0;39m", STDOUT_FILENO);
    }
}