/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkasongo <jkasongo@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 15:02:59 by jkasongo          #+#    #+#             */
/*   Updated: 2022/03/12 13:47:30 by jkasongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

// check if we potentially have a shell special char
bool	ft_is_special_shell_char(char value)
{
	if (value == '|' || value == ';' || value == '&' ||
		value == '>' || value == '<' || value == '*' ||
		value == '(' || value == ')' || value == '$')
	{
		return (true);
	}
	return (false);
}

// check if from cursor( ' or " ) we have a closed quote or no
bool	check_quote(char *sentence, size_t cursor, size_t len, char q)
{
	cursor++;
	while (cursor < len)
	{
		if (sentence[cursor] == q)
			return (true);
		cursor++;
	}
	return (false);
}

// check if single or double quote
bool	ft_is_a_quote_char(char value)
{
	return (value == 34 || value == 39);
}

char	*ft_concat_char(char *str, char c)
{
	size_t	len;
	char	*heap_p;

	if ((str == NULL) && (c == 0))
		return (ft_strdup(""));
	len = ft_strlen(str);
	if ((len == 0) && (c != 0))
	{
		heap_p = (char *)malloc(2);
		heap_p[0] = c;
		heap_p[1] = 0;
	}
	else
	{
		heap_p = (char *)malloc(len + 2);
		if (!heap_p)
			return (0);
		ft_memmove(heap_p, str, len);
		heap_p[len] = c;
		heap_p[len + 1] = 0;
	}
	free(str);
	return (heap_p);
}

void	build_error_token(t_token *token, size_t cursor, int error)
{

	token->type = e_token_error;
	token->start_pos = cursor;
	token->end_pos = cursor;
	if (error == 1)
		token->value = ft_strdup("Quote Error\n");
}
