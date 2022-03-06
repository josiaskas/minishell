/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_str.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkasongo <jkasongo@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/26 18:12:09 by jkasongo          #+#    #+#             */
/*   Updated: 2021/06/04 23:20:44 by jkasongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void	ft_print_with_zero_str(t_arg *arg, char *str, int len)
{
	int	width;

	width = 0;
	if (arg->part[1])
		width = arg->min_width;
	if (width < 0)
		width *= -1;
	arg->written = 0;
	while (width > len)
	{
		write(STDOUT_FILENO, "0", 1);
		arg->written++;
		width--;
	}
	arg->written += len;
	ft_putstr_fd(str, STDOUT_FILENO);
}

void	ft_print_right_aligned_str(t_arg *arg, char *str, int len)
{
	int	width;

	width = 0;
	if (arg->part[1])
		width = arg->min_width;
	if (width < 0)
		width *= -1;
	arg->written = 0;
	while (width > len)
	{
		write(STDOUT_FILENO, " ", 1);
		arg->written++;
		width--;
	}
	arg->written += len;
	ft_putstr_fd(str, STDOUT_FILENO);
}

void	ft_print_left_aligned_str(t_arg *arg, char *str, int len)
{
	int	width;

	arg->written = 0;
	arg->written += len;
	ft_putstr_fd(str, STDOUT_FILENO);
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

void	print_special(char *flag, int len, char *str, t_arg *arg)
{
	char	*tmp;

	arg->written = 0;
	tmp = 0;
	if (arg->part[2] && (arg->max_precision < len))
	{
		tmp = ft_strndup(str, arg->max_precision);
		str = tmp;
		len = arg->max_precision;
	}
	if (flag[e_minus])
		ft_print_left_aligned_str(arg, str, len);
	else if (flag[e_zero])
		ft_print_with_zero_str(arg, str, len);
	else if (arg->part[1] && (arg->min_width < 0))
		ft_print_left_aligned_str(arg, str, len);
	else
		ft_print_right_aligned_str(arg, str, len);
	free(tmp);
	return ;
}

void	ft_printf_str(t_arg *arg)
{
	int		len;
	char	*str;
	char	*null;

	str = va_arg(arg->args, char *);
	len = ft_strlen(str);
	null = "(null)";
	if (!str)
	{
		str = null;
		len = 6;
	}
	if (arg->part[0] || arg->part[1] || arg->part[2])
		print_special(arg->flag, len, str, arg);
	else
	{
		ft_putstr_fd(str, STDOUT_FILENO);
		arg->written = len;
	}
	return ;
}
