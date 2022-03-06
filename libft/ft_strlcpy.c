/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkasongo <jkasongo@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 02:20:58 by jkasongo          #+#    #+#             */
/*   Updated: 2021/05/07 17:23:27 by jkasongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t		copied;
	const char	*s_begin = src;

	copied = 0;
	if ((dst == 0) || (src == 0))
		return (0);
	while ((*src != 0) && (copied < (dstsize - 1)) && (dstsize != 0))
	{
		*dst = *src;
		copied++;
		src++;
		dst++;
	}
	if (dstsize != 0)
		*dst = 0;
	while (*src != 0)
		src++;
	return (src - s_begin);
}
