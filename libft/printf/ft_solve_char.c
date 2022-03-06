/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_solve_char.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkasongo <jkasongo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/25 13:46:38 by jkasongo          #+#    #+#             */
/*   Updated: 2021/06/19 06:43:39 by jkasongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static void	ft_print_with_zero(t_arg *arg, int width)
{
	char	c;

	if (width < 0)
		width = (-1) * width;
	if (width > 1)
		arg->written = width;
	else
		arg->written = 1;
	while ((width - 1) > 0)
	{
		write(STDOUT_FILENO, "0", 1);
		width--;
	}
	c = va_arg(arg->args, int);
	ft_putchar_fd(c, STDOUT_FILENO);
	return ;
}

static void	ft_print_rigth_aligned(t_arg *arg, int width)
{
	char	c;

	if (width < 0)
		width *= -1;
	if (width > 1)
		arg->written = width;
	else
		arg->written = 1;
	while ((width - 1) > 0)
	{
		write(STDOUT_FILENO, " ", 1);
		width--;
	}
	c = va_arg(arg->args, int);
	ft_putchar_fd(c, STDOUT_FILENO);
	return ;
}

static void	ft_print_left_aligned(t_arg *arg, int width)
{
	char	c;

	if (width < 0)
		width *= -1;
	c = va_arg(arg->args, int);
	write(STDOUT_FILENO, &c, 1);
	if (width > 1)
		arg->written = width;
	else
		arg->written = 1;
	while ((width - 1) > 0)
	{
		write(STDOUT_FILENO, " ", 1);
		width--;
	}
	return ;
}

static void	print_special(char *flag, int width, t_arg *arg)
{
	if (flag[e_minus])
	{
		ft_print_left_aligned(arg, width);
		return ;
	}
	if (flag[e_zero])
	{
		ft_print_with_zero(arg, width);
		return ;
	}
	if (width < 0)
		ft_print_left_aligned(arg, width);
	else
		ft_print_rigth_aligned(arg, width);
	return ;
}

void	ft_printf_char(t_arg *arg)
{
	int		width;
	char	*flag;
	char	c;

	width = 1;
	flag = arg->flag;
	if (arg->part[1])
		width = arg->min_width;
	if ((arg->part[0]) || (width > 1) || (width < -1))
		print_special(arg->flag, width, arg);
	else
	{
		c = va_arg(arg->args, int);
		if (c == 0)
			write(STDOUT_FILENO, "\x00", 1);
		else
			ft_putchar_fd(c, STDOUT_FILENO);
		arg->written = 1;
	}
}
