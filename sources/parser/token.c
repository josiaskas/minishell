/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkasongo <jkasongo@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 14:50:24 by jkasongo          #+#    #+#             */
/*   Updated: 2022/03/13 19:19:50 by jkasongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

// build the string token and escape char
void	ft_str_tok(t_token *tok, char *str, size_t cursor, size_t len)
{
	char	*word;
	char	next_c;

	tok->type = e_token_text;
	tok->start_pos = cursor;
	word = NULL;
	while (cursor < len)
	{
		next_c = str[cursor + 1];
		if (ft_isspace(str[cursor]) || ft_is_special_shell_char(str[cursor]))
			break ;
		else if ((str[cursor] == 92)
			&& (ft_is_special_shell_char(next_c) || (next_c == 92)))
		{
			word = ft_concat_char(word, next_c);
			cursor++;
		}
		else
			word = ft_concat_char(word, str[cursor]);
		cursor++;
	}
	tok->value = word;
	tok->end_pos = cursor;
}

// build logic operator token
void	ft_op_tok(t_token *token, char *sentence, size_t cursor)
{
	token->start_pos = cursor;
	token->end_pos = cursor + 1;
	if (sentence[cursor] == '&')
	{
		token->type = e_token_and_and;
		token->value = ft_strdup("&&");
		token->end_pos = cursor + 2;
	}
	if (sentence[cursor] == '|')
	{
		token->type = e_token_or;
		token->value = ft_strdup("||");
		token->end_pos = cursor + 2;
	}
}

// build shell special token and EOF token
void	ft_sp_tok(t_token *token, char *sentence, size_t cursor)
{
	int	t;

	t = token->type;
	token->start_pos = cursor;
	token->end_pos = cursor;
	if (t == e_token_eof)
	{
		token->value = NULL;
		return ;
	}
	if (t == e_token_greater_greater)
	{
		token->value = ft_strdup(">>");
		cursor++;
	}
	else if (t == e_token_less_less)
	{
		token->value = ft_strdup("<<");
		cursor++;
	}
	else
		token->value = ft_concat_char(NULL, sentence[cursor]);
	token->end_pos = cursor + 1;
}
