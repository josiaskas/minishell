/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkasongo <jkasongo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 03:54:47 by jkasongo          #+#    #+#             */
/*   Updated: 2021/08/07 22:59:10 by jkasongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_isspace_local(int c)
{
	if (c == ' ' || c == '\t' || c == '\n'
		|| c == '\v' || c == '\f' || c == '\r')
		return (1);
	else
		return (0);
}

int	ft_atoi(const char *str)
{
	long	nbr;
	int		sign;
	int		i;

	i = 0;
	nbr = 0;
	sign = 1;
	if (!str)
		return (0);
	while (str[i] != 0 && ft_isspace_local(str[i]))
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
		return ((int)(nbr * -1));
	return ((int)nbr);
}
