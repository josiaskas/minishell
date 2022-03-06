/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_width.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkasongo <jkasongo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/24 13:54:23 by jkasongo          #+#    #+#             */
/*   Updated: 2021/06/19 06:33:06 by jkasongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static void	mini_itoa_width(t_arg *arg, char c)
{
	int	width;

	width = 0;
	while ((c >= '0') && (c <= '9'))
	{
		width = width * 10;
		width += (int)(c - 48);
		arg->part[1] = 1;
		arg->cursor++;
		c = arg->format[arg->cursor];
	}
	arg->min_width = width;
}

//[1-9 (only if flag specified first, not true) or * (value inside the args)]
void	ft_parse_width(t_arg *arg)
{
	int		width;
	char	c;

	width = 0;
	arg->part[1] = 0;
	arg->min_width = 0;
	c = arg->format[arg->cursor];
	if (c == '*')
	{
		width = va_arg(arg->args, int);
		arg->min_width = width;
		arg->part[1] = 1;
		arg->cursor++;
		return ;
	}
	if ((c >= '1') && (c <= '9'))
		mini_itoa_width(arg, c);
	return ;
}
