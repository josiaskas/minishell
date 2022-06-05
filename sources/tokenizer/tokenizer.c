/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkasongo <jkasongo@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 13:52:57 by jkasongo          #+#    #+#             */
/*   Updated: 2022/05/04 12:32:52 by jkasongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

// check if we potentially have a shell special char
bool	ft_is_special_shell_char(char value)
{
	if (value == '|' || value == ';' || value == '&'
		|| value == '>' || value == '<' || value == '*'
		|| value == '(' || value == ')' || value == '$'
		|| value == 34 || value == 39 || value == 92
		|| value == '{' || value == '}' || value == '~'
		|| value == '#')
	{
		return (true);
	}
	return (false);
}


t_tokeniser	*init_tokenizer(char *sentence)
{
	t_tokeniser	*lexical_int;
	t_array		*tokens;

	lexical_int = NULL;
	tokens = NULL;
	lexical_int = (t_tokeniser *)ft_calloc(1, sizeof(t_tokeniser));
	if (!lexical_int)
		return (NULL);
	lexical_int->cursor = 0;
	lexical_int->sentence = sentence;
	lexical_int->len = ft_strlen(sentence);
	tokens = ft_new_array();
	if (!tokens)
		return (NULL);
	lexical_int->tokens = tokens;
	return (lexical_int);
}

// free memory of the tokenizer build, token value also
void	destroy_tokinizer(t_tokeniser *lexical)
{
	t_token	*content;

	if (!lexical)
		return;
	while (lexical->tokens->length)
	{
		content = (t_token *)ft_pop(lexical->tokens);
		free(content->value);
		free(content->meta);
		free(content);
	}
	free(lexical->tokens);
	free(lexical);
}

// build and return the next token on demand
t_token	*get_next_token(t_tokeniser *lexical)
{
	size_t	cursor;
	char	current;

	cursor = lexical->cursor;
	current = lexical->sentence[cursor];
	if (lexical->cursor >= lexical->len)
		return (build_token(e_token_eof, lexical, cursor));
	else if (ft_isspace(current) && (current != 0))
		return (build_token(e_token_space, lexical, cursor));
	if (ft_is_special_shell_char(current))
		return (build_spec_t(lexical, cursor, current));
	else
		return (build_token(e_token_text, lexical, cursor));
}

// build a string by adding a char c
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
