/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_printf.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkasongo <jkasongo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/08 20:58:58 by jkasongo          #+#    #+#             */
/*   Updated: 2021/06/14 23:03:52 by jkasongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static size_t	ft_nbr_char(long big)
{
	size_t	nbr;

	nbr = 0;
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

static void	ft_putnbr_str(long nbr, char *str, size_t i)
{
	if (nbr < 0)
	{
		str[0] = '-';
		nbr = -nbr;
	}
	if (nbr > 9)
		ft_putnbr_str((nbr / 10), str, (i - 1));
	str[i] = (char)('0' + (nbr % 10));
}

char	*ft_itoa_printf(long n)
{
	char	*str;
	size_t	len;

	len = ft_nbr_char(n);
	str = ft_calloc(1, len + 2);
	if (!str)
		return (0);
	ft_putnbr_str(n, str, len);
	str[len + 1] = 0;
	return (str);
}
