/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkasongo <jkasongo@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 00:24:38 by jkasongo          #+#    #+#             */
/*   Updated: 2022/03/25 20:04:16 by jkasongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

// print the lexical analyzer result
void	ft_print_token(void *data, int index)
{
	t_token	*token;

	(void) index;
	token = (t_token *)data;
	if (token->type == e_token_text)
		ft_printf("{{ %s }}", token->value);
	else if (token->type == e_token_eof)
		ft_putstr_fd("\033[0;31mEOF\033[0;39m", STDOUT_FILENO);
	else if ((token->type == e_token_subst) || (token->type == e_token_or)
			|| (token->type == e_token_double_and) || token->type == e_token_semicolon)
	{
		ft_printf("\033[0;31m%s\033[0;39m", token->value);
	}
	else if ((token->type == e_token_quote) || (token->type == e_token_dquote) || (token->type == e_token_space))
		ft_printf("\033[0;32m%s\033[0;39m", token->value);
	else if ((token->type == e_token_dollar)
		|| (token->type == e_token_wildcard)
		|| (token->type == e_token_tilde))
		ft_printf("\033[0;35m%s\033[0;39m", token->value);
	else
		ft_printf("\033[0;33m-%s-\033[0;39m", token->value);
}

// parse line if error return an error code
int	parse_line(char *sentence)
{
	t_tokeniser		*lexical_anyliser;
	t_token			*token;
	size_t			i;

	lexical_anyliser = init_tokenizer(sentence);
	token = get_next_token(lexical_anyliser);
	while (token->type != e_token_eof)
		token = get_next_token(lexical_anyliser);
	i = 0;
	ft_for_each(lexical_anyliser->tokens, ft_print_token);
	destroy_tokinizer(lexical_anyliser);
	return (0);
}
