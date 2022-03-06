/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkasongo <jkasongo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/23 13:18:28 by jkasongo          #+#    #+#             */
/*   Updated: 2021/08/07 22:17:59 by jkasongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static int	ft_parse_format(t_arg *arg)
{
	int	is_arg;

	is_arg = 1;
	arg->written = 0;
	arg->cursor++;
	ft_bzero(arg->flag, 4);
	ft_bzero(arg->part, 4);
	if (arg->format[arg->cursor] != 0)
		ft_parse_flag(arg);
	if (arg->format[arg->cursor] != 0)
		ft_parse_width(arg);
	if (arg->format[arg->cursor] != 0)
		ft_parse_precision(arg);
	if (arg->format[arg->cursor] != 0)
		ft_parse_arg_type(arg);
	if (arg->part[3])
		ft_write_arg_data(arg);
	else
		is_arg = 0;
	return (is_arg);
}

static int	ft_write_arg(t_arg *arg)
{
	int	written;

	arg->cursor_arg = arg->cursor;
	arg->written = 0;
	written = 0;
	if (ft_parse_format(arg))
		written += arg->written;
	else
	{
		while ((arg->cursor_arg) < (arg->cursor))
		{
			ft_putchar_fd(arg->format[arg->cursor_arg], STDOUT_FILENO);
			arg->cursor_arg++;
			written++;
		}
	}
	return (written);
}

static int	ft_loop_format(t_arg *arg)
{
	int		written;

	written = 0;
	while (arg->format[arg->cursor] != 0)
	{
		if ((arg->format[arg->cursor] == '%')
			&& (arg->format[arg->cursor + 1] != '%'))
			written += ft_write_arg(arg);
		else if ((arg->format[arg->cursor] == '%')
			&& (arg->format[arg->cursor + 1] == '%'))
		{
			ft_putchar_fd(arg->format[arg->cursor + 1], STDOUT_FILENO);
			written++;
			arg->cursor += 2;
		}
		else
		{
			ft_putchar_fd(arg->format[arg->cursor], STDOUT_FILENO);
			written++;
			arg->cursor++;
		}
	}
	return (written);
}

int	ft_printf(const char *format, ...)
{
	int		total_written;
	t_arg	arg;

	va_start(arg.args, format);
	total_written = 0;
	arg.format = format;
	arg.cursor = 0;
	total_written = ft_loop_format(&arg);
	va_end(arg.args);
	if (total_written < 0)
		return (0);
	return (total_written);
}
