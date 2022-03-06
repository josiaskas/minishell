/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkasongo <jkasongo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/27 16:41:20 by jkasongo          #+#    #+#             */
/*   Updated: 2021/08/07 23:00:03 by jkasongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

char	*ft_precision_spaces(char *str, int precision, int len, t_arg *arg)
{
	char	*cpy;
	int		diff;

	diff = precision - len;
	cpy = ft_calloc(1, (precision + 1));
	if (diff > 0)
		cpy = ft_memset(cpy, ' ', diff);
	else
		diff = 0;
	if (arg->part[1] && (arg->min_width < 0))
		diff = 0;
	if (!arg->part[1])
		diff = 0;
	ft_strlcpy((cpy + diff), str, (precision + 1));
	return (cpy);
}

char	*ft_precision_zeros(char *str, int precision, int len)
{
	char	*cpy;
	int		diff;

	diff = precision - len;
	cpy = ft_calloc(1, (precision + 1));
	if (diff > 0)
		cpy = ft_memset(cpy, '0', diff);
	else
		diff = 0;
	ft_strlcpy((cpy + diff), str, (len + 1));
	return (cpy);
}

void	ft_itoa_hex(char *str, unsigned long long nbr)
{
	int		i;
	char	*base;

	i = 0;
	base = "0123456789abcdef";
	if (nbr == 0)
		str[i++] = '0';
	while (nbr > 0)
	{
		str[i++] = base[(nbr % 16)];
		nbr /= 16;
	}
	str[i] = 0;
	ft_strrev(str);
	return ;
}
