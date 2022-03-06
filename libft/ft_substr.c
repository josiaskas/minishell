/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkasongo <jkasongo@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/07 23:57:30 by jkasongo          #+#    #+#             */
/*   Updated: 2021/05/08 00:53:53 by jkasongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while ((s[i] != 0))
		i++;
	if ((i > start))
	{
		sub = malloc(len + 1);
		if (!sub)
			return (0);
		i = 0;
		while ((s[start] != 0) && (i < len))
			sub[i++] = s[start++];
		sub[i] = 0;
		return (sub);
	}
	else
		return (ft_strdup(""));
}
