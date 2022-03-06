/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkasongo <jkasongo@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/09 13:16:58 by jkasongo          #+#    #+#             */
/*   Updated: 2021/08/09 15:52:30 by jkasongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long	ft_atol(const char *str)
{
	long	nbr;
	int		sign;
	int		i;

	nbr = 0;
	i = 0;
	sign = 1;
	if (!str)
		return (0);
	while (str[i] != 0 && ft_isspace(str[i]))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i] != 0 && ft_isdigit(str[i]))
		nbr = (nbr * 10) + (str[i++] - '0');
	if (sign == -1)
		return ((long)(nbr * -1));
	return (nbr);
}
