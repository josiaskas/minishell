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


int	parse_line(char *sentence)
{
	t_tokeniser *lexical_anyliser;
	t_token     *token;
    t_array     *lexer;

	lexical_anyliser = init_tokenizer(sentence);
	token = get_next_token(lexical_anyliser);
	while (token->type != e_token_eof)
		token = get_next_token(lexical_anyliser);
    lexer = run_simple_lexer(lexical_anyliser->tokens);
    ft_for_each(lexer, ft_print_lex);
    destroy_lexer(lexer);
	destroy_tokinizer(lexical_anyliser);
	return (0);
}
