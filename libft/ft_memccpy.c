/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkasongo <jkasongo@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/07 16:56:54 by jkasongo          #+#    #+#             */
/*   Updated: 2021/05/07 17:22:25 by jkasongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	const unsigned char	*s;
	unsigned char		*d;
	unsigned char		byte;
	size_t				i;

	byte = (unsigned char)c;
	if ((!dst && !src) || (n == 0))
		return (0);
	s = (const unsigned char *)src;
	d = (unsigned char *)dst;
	i = 0;
	while (i < n)
	{
		d[i] = s[i];
		if (d[i] == byte)
			return (dst + i + 1);
		i++;
	}
	return (0);
}
