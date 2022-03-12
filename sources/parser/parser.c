/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkasongo <jkasongo@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 00:24:38 by jkasongo          #+#    #+#             */
/*   Updated: 2022/03/12 14:10:36 by jkasongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"

void	parse_args(char *sentence)
{
	t_tokeniser	*lexical_anyliser;
	t_token		*token;

	lexical_anyliser = init_tokenizer(sentence);
	token = get_next_token(lexical_anyliser);
	while (token->type != e_token_eof)
	{
		if (token->type == e_token_error)
		{
			ft_printf("\033[0;31m %s \033[0;39m", token->value);
			break ;
		}
		if (token->type == e_token_text)
			ft_printf("-w-%s-", token->value);
		else
		{
			ft_printf("\033[0;32m%s\033[0;39m", token->value);
		}
		// printf("position : %ld type: %d\n", lexical_anyliser->cursor, token->type);
		token = get_next_token(lexical_anyliser);
	}
	ft_putendl_fd(" ",STDOUT_FILENO);
	destroy_tokinizer(lexical_anyliser);
}
