/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkasongo <jkasongo@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/08 20:58:58 by jkasongo          #+#    #+#             */
/*   Updated: 2021/05/11 14:42:08 by jkasongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_nbr_char(int n)
{
	size_t	nbr;
	long	big;

	nbr = 0;
	big = (long)n;
	if (big < 0)
	{
		big = -big;
		nbr++;
	}
	while (big > 9)
	{
		big /= 10;
		nbr++;
	}
	return (nbr);
}

static void	ft_putnbr_str(int n, char *str, size_t i)
{
	long	nbr;

	nbr = (long)n;
	if (nbr < 0)
	{
		str[0] = '-';
		nbr = -nbr;
	}
	if (nbr > 9)
		ft_putnbr_str((nbr / 10), str, (i - 1));
	str[i] = (char)('0' + (nbr % 10));
}

char	*ft_itoa(int n)
{
	char	*str;
	size_t	len;

	len = ft_nbr_char(n);
	str = malloc(len + 2);
	if (!str)
		return (0);
	ft_putnbr_str(n, str, len);
	str[len + 1] = 0;
	return (str);
}
