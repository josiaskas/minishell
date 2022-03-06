/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_solve_int.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkasongo <jkasongo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/04 20:51:04 by jkasongo          #+#    #+#             */
/*   Updated: 2021/06/19 06:35:59 by jkasongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static void	ft_print_with_zero(t_arg *arg, char *str, int len, int sign)
{
	int	width;

	width = 0;
	if (arg->part[1])
		width = arg->min_width;
	arg->written = 0;
	if (sign < 1)
	{
		len++;
		write(STDOUT_FILENO, "-", 1);
	}
	while (width > len)
	{
		write(STDOUT_FILENO, "0", 1);
		arg->written++;
		width--;
	}
	ft_putstr_fd(str, STDOUT_FILENO);
	arg->written += len;
}

static void	ft_print_right_aligned(t_arg *arg, char *str, int len, int sign)
{
	int	width;

	width = 0;
	if (arg->part[1])
		width = arg->min_width;
	if (width < 0)
		width *= -1;
	arg->written = 0;
	if (sign < 1)
		len++;
	while (width > len)
	{
		write(STDOUT_FILENO, " ", 1);
		arg->written++;
		width--;
	}
	arg->written += len;
	if (sign < 1)
		write(STDOUT_FILENO, "-", 1);
	ft_putstr_fd(str, STDOUT_FILENO);
}

static void	ft_print_left_aligned(t_arg *arg, char *str, int len, int sign)
{
	int	width;

	if (sign < 1)
	{
		len++;
		write(STDOUT_FILENO, "-", 1);
	}
	ft_putstr_fd(str, STDOUT_FILENO);
	arg->written += len;
	width = 0;
	if (arg->part[1])
		width = arg->min_width;
	if (width < 0)
		width *= -1;
	while (width > len)
	{
		write(STDOUT_FILENO, " ", 1);
		arg->written++;
		width--;
	}
}

static void	print_special(char *flag, char *str, int sign, t_arg *arg)
{
	char	*str_precised;
	int		len;

	arg->written = 0;
	str_precised = NULL;
	len = ft_strlen(str);
	if (arg->flag[e_space] && (sign > 0) && (!arg->flag[e_plus]))
		write(STDOUT_FILENO, " ", 1);
	if (arg->part[2] && (arg->max_precision > len))
		str_precised = ft_precision_zeros(str, arg->max_precision, len);
	else if (str[0] == '0' && (arg->part[2] && arg->max_precision == 0))
		str_precised = ft_strndup("", 2);
	else
		str_precised = ft_strndup(str, len);
	len = ft_strlen(str_precised);
	if (flag[e_minus])
		ft_print_left_aligned(arg, str_precised, len, sign);
	else if (flag[e_zero] && (!arg->part[2]) && (arg->min_width > 0))
		ft_print_with_zero(arg, str_precised, len, sign);
	else if (arg->part[1] && (arg->min_width < 0))
		ft_print_left_aligned(arg, str_precised, len, sign);
	else
		ft_print_right_aligned(arg, str_precised, len, sign);
	free(str_precised);
}

void	ft_printf_int(t_arg *arg)
{
	long	nbr;
	int		sign;
	char	*str;
	int		len;

	nbr = (long)va_arg(arg->args, int);
	sign = 1;
	if (nbr < 0)
		sign = -1;
	str = ft_itoa_printf((nbr * (long)sign));
	len = ft_strlen(str);
	if (arg->part[0] || arg->part[1] || arg->part[2])
		print_special(arg->flag, str, sign, arg);
	else
	{
		if (sign == -1)
		{
			len++;
			write(STDOUT_FILENO, "-", 1);
		}
		ft_putstr_fd(str, STDOUT_FILENO);
		arg->written = len;
	}
	free(str);
	return ;
}
