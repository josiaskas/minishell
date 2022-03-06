/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkasongo <jkasongo@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 02:40:25 by jkasongo          #+#    #+#             */
/*   Updated: 2021/05/06 03:55:16 by jkasongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*found;

	found = 0;
	while (*s != 0)
	{
		if (*s == c)
			found = (char *)s;
		s++;
	}
	if (*s == c)
		return ((char *)s);
	return (found);
}
