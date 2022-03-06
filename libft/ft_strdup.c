/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkasongo <jkasongo@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/08 17:53:04 by jkasongo          #+#    #+#             */
/*   Updated: 2021/05/08 17:53:05 by jkasongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"libft.h"

char	*ft_strdup(const char *s1)
{
	char	*heap_p;
	char	*p;
	size_t	len;

	len = 0;
	while (s1[len])
		len++;
	heap_p = malloc(len + 1);
	if (!heap_p)
		return (0);
	p = heap_p;
	while (*s1 != 0)
		*p++ = *s1++;
	*p = '\0';
	return (heap_p);
}
