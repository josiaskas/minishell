/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_precision.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkasongo <jkasongo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/24 13:44:37 by jkasongo          #+#    #+#             */
/*   Updated: 2021/06/19 06:32:54 by jkasongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static void	mini_itoa_precision(t_arg *arg, char c)
{
	int	precision;

	precision = 0;
	while ((c >= '0') && (c <= '9'))
	{
		precision = precision * 10;
		precision += (int)(c - 48);
		arg->part[2] = 1;
		arg->cursor++;
		c = arg->format[arg->cursor];
	}
	arg->max_precision = precision;
}

//[0-9] number or * (value inside the args) never negative start from 0 to n]
void	ft_parse_precision(t_arg *arg)
{
	int		precision ;
	char	c;

	precision = 0;
	arg->part[2] = 0;
	if ((arg->format[arg->cursor]) != '.')
		return ;
	arg->max_precision = 0;
	arg->part[2] = 1;
	arg->cursor++;
	if ((arg->format[arg->cursor]) == '*')
	{
		precision = va_arg(arg->args, int);
		arg->max_precision = precision;
		arg->part[2] = 1;
		if (precision < 0)
			arg->part[2] = 0;
		arg->cursor++;
		return ;
	}
	c = arg->format[arg->cursor];
	if ((c >= '0') && (c <= '9'))
		mini_itoa_precision(arg, c);
	return ;
}
