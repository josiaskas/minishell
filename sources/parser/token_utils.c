/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkasongo <jkasongo@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 15:02:59 by jkasongo          #+#    #+#             */
/*   Updated: 2022/03/13 19:18:43 by jkasongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

// free memory of the tokenizer build, token value also
void	destroy_tokinizer(t_tokeniser *lexical)
{
	t_token	*content;

	if (!lexical)
		return ;
	while (lexical->tokens->length)
	{
		content = pop(lexical->tokens);
		free(content->value);
		free(content);
	}
	free(lexical->tokens);
	free(lexical);
}

// check if we potentially have a shell special char
bool	ft_is_special_shell_char(char value)
{
	if (value == '|' || value == ';' || value == '&'
		|| value == '>' || value == '<' || value == '*'
		|| value == '(' || value == ')' || value == '$'
		|| value == 34 || value == 39)
	{
		return (true);
	}
	return (false);
}

// check if from cursor( ' or " ) we have a closed quote or no
bool	is_close_quote(char *sentence, size_t cursor, size_t len, char q)
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

// check if single(1) or double quote(2) or no quote(0)
int	ft_is_a_quote_char(char value)
{
	if (value == 34)
		return (2);
	else if (value == 39)
		return (1);
	else
		return (0);
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
