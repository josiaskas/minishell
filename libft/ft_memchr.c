/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkasongo <jkasongo@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/07 17:19:09 by jkasongo          #+#    #+#             */
/*   Updated: 2021/05/07 17:19:51 by jkasongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char	*str;
	unsigned char		byte;

	str = (const unsigned char *)s;
	byte = (unsigned char)c;
	while (n--)
	{
		if (*str == byte)
			return ((void *)(str));
		str++;
	}
	return (0);
}
