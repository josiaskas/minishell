/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_flag.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkasongo <jkasongo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/24 13:54:46 by jkasongo          #+#    #+#             */
/*   Updated: 2021/06/19 06:32:43 by jkasongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static int	ft_transform_flag(char c)
{
	if (c == '-')
		return (e_minus);
	if (c == '0')
		return (e_zero);
	if (c == ' ')
		return (e_space);
	if (c == '+')
		return (e_plus);
	return (e_minus);
}

void	ft_parse_flag(t_arg *arg)
{
	char	c;

	c = arg->format[arg->cursor];
	arg->part[0] = 0;
	arg->flag[e_minus] = 0;
	arg->flag[e_zero] = 0;
	arg->flag[e_space] = 0;
	arg->flag[e_plus] = 0;
	while ((c == '-') || (c == '+') || (c == ' ') || (c == '#') || (c == '0'))
	{
		arg->flag[ft_transform_flag(c)] = 1;
		arg->part[0] = 1;
		arg->cursor++;
		c = arg->format[arg->cursor];
	}
	return ;
}
