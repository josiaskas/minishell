/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkasongo <jkasongo@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 00:24:38 by jkasongo          #+#    #+#             */
/*   Updated: 2022/03/13 23:33:36 by jkasongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

// print the lexical analyzer result
void	ft_print_token(t_token *token)
{
	if (token->type == e_token_text)
		ft_printf(" -( %s )- ", token->value);
	else if ((token->type == e_token_left_paren) || (token->type == e_token_right_paren) || (token->type == e_token_and_and) || (token->type == e_token_or))
	{
		ft_printf("\033[0;31m -%s- \033[0;39m", token->value);
	}
	else if ((token->type == e_token_quote) || (token->type == e_token_dquote))
		ft_printf("\033[0;32m -%s- \033[0;39m", token->value);
	else if (token->type == e_token_dollar)
		ft_printf("\033[0;35m -%s-\033[0;39m", token->value);
	else
		ft_printf("\033[0;33m -%s-\033[0;39m", token->value);
}

// parse line if error return an error code
int	parse_line(char *sentence)
{
	t_tokeniser	*lexical_anyliser;
	t_token		*token;

	lexical_anyliser = init_tokenizer(sentence);
	token = get_next_token(lexical_anyliser);
	while (token->type != e_token_eof)
	{
		ft_print_token(token);
		token = get_next_token(lexical_anyliser);
	}
	destroy_tokinizer(lexical_anyliser);
	return (0);
}
