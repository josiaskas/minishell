/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkasongo <jkasongo@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/07 22:51:47 by jkasongo          #+#    #+#             */
/*   Updated: 2021/05/07 22:51:47 by jkasongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(const char *s1, size_t n)
{
	char	*heap_p;
	char	*p;

	heap_p = malloc(n + 1);
	if (!heap_p)
		return (0);
	p = heap_p;
	while ((*s1 != 0) && (n--))
		*p++ = *s1++;
	*p = '\0';
	return (heap_p);
}
