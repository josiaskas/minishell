/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkasongo <jkasongo@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 12:46:36 by jkasongo          #+#    #+#             */
/*   Updated: 2022/06/25 16:33:46 by jkasongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/tokenizer.h"

/*
 * return true if string is only numbers
 */
bool	ft_is_a_number(char *str)
{
	size_t	size;
	size_t	i;

	size = ft_strlen(str);
	if (size == 0)
		return (false);
	i = 0;
	while (i < size)
	{
		if (!ft_isdigit(str[i]))
			return (false);
		i++;
	}
	return (true);
}

/*
 * return a text fetch inside the senetence
 */
char	*get_word_in_sentence(size_t cursor, char *str, size_t len)
{
	char	*word;

	word = NULL;
	while (cursor < len)
	{
		if (ft_isspace(str[cursor]) || ft_is_special_shell_char(str[cursor]))
			break ;
		else
			word = ft_concat_char(word, str[cursor]);
		cursor++;
	}
	return (word);
}
