/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkasongo <jkasongo@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 02:23:35 by jkasongo          #+#    #+#             */
/*   Updated: 2021/05/06 03:38:44 by jkasongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	c;
	size_t	j;
	size_t	neddle_size;
	char	*found;

	found = 0;
	c = 0;
	neddle_size = ft_strlen(needle);
	if (neddle_size == 0 || haystack == needle)
		return ((char *)haystack);
	while ((haystack[c] != 0) && (c < len))
	{
		j = 0;
		while ((haystack[c + j] == needle[j]) && (haystack[c + j] != 0)
			&& (needle[j] != 0) && (c + j < len))
			j++;
		if (j == neddle_size)
		{
			found = (char *)(haystack + c);
			return (found);
		}
		c++;
	}
	return (found);
}
