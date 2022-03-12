/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkasongo <jkasongo@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 14:50:24 by jkasongo          #+#    #+#             */
/*   Updated: 2022/03/12 14:08:07 by jkasongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

// check if we have a closed quote or no
static bool close_quote(char *str, size_t cursor, size_t len, char q)
{
	cursor++;
	while (cursor < len)
	{
		if (str[cursor] == q)
			return (true);
		cursor++;
	}
	return (false);
}

static void	ft_quote(t_token *tok, char *str, size_t cur, size_t len)
{
	char quote;
	char *word;

	tok->type = e_token_text;
	tok->start_pos = cur;
	word = NULL;
	quote = str[cur];
	if (!close_quote(str, cur, len, quote))
	{
		build_error_token(tok, cur, 1);
		return;
	}
	cur++;
	while (cur < len)
	{
		if (str[cur] == quote)
		{
			cur++;
			break;
		}
		else
			word = ft_concat_char(word, str[cur]);
		cur++;
	}
	tok->value = word;
	tok->end_pos = cur;
}

// build the string token
void	ft_str_tok(t_token *tok, char *str, size_t cursor, size_t len)
{
	char	*word;

	tok->type = e_token_text;
	tok->start_pos = cursor;
	word = NULL;
	if (ft_is_a_quote_char(str[cursor]))
	{
		ft_quote(tok, str, cursor, len);
		return ;
	}
	while (cursor < len)
		{
			if (ft_isspace(str[cursor]) || ft_is_special_shell_char(str[cursor]))
				break;
			else if (ft_is_a_quote_char(str[cursor]))
				break;
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
