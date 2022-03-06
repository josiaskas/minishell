/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_arg_type.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkasongo <jkasongo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/24 13:53:47 by jkasongo          #+#    #+#             */
/*   Updated: 2021/06/19 06:32:23 by jkasongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void	ft_parse_arg_type(t_arg *arg)
{
	char	c;

	c = arg->format[arg->cursor];
	arg->part[3] = 0;
	if ((c == 'c') || (c == 's') || (c == 'p') || (c == 'd') || (c == 'i')
		|| (c == 'u') || (c == 'x') || (c == 'X') || (c == '%'))
	{
		arg->arg_type = c;
		arg->cursor++;
		arg->part[3] = 1;
	}
}

void	ft_write_arg_data(t_arg *arg)
{
	if (arg->arg_type == 'c')
		ft_printf_char(arg);
	if (arg->arg_type == 's')
		ft_printf_str(arg);
	if (arg->arg_type == 'p')
		ft_printf_pointer(arg);
	if ((arg->arg_type == 'd') || (arg->arg_type == 'i'))
		ft_printf_int(arg);
	if (arg->arg_type == 'u')
		ft_printf_unsigned(arg);
	if ((arg->arg_type == 'x') || (arg->arg_type == 'X'))
		ft_printf_hexadecimal(arg);
	if (arg->arg_type == '%')
		ft_printf_pourcentage(arg);
}
