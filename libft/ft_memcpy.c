/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkasongo <jkasongo@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/07 16:11:53 by jkasongo          #+#    #+#             */
/*   Updated: 2021/05/07 17:22:54 by jkasongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	const unsigned char	*s;
	unsigned char		*d;

	if ((dst == src) || n == 0)
		return (dst);
	if (!dst && !src)
		return (0);
	s = (const unsigned char *)src;
	d = (unsigned char *)dst;
	while (n--)
		d[n] = s[n];
	return (dst);
}
