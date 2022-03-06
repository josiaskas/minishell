/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_pointer.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkasongo <jkasongo@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/28 11:42:21 by jkasongo          #+#    #+#             */
/*   Updated: 2021/05/28 19:12:53 by jkasongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static void	ft_print_with_zero(t_arg *arg, char *str, int len)
{
	int	width;

	width = 0;
	if (arg->part[1])
		width = arg->min_width;
	arg->written = 0;
	len += 2;
	ft_putstr_fd("0x", STDOUT_FILENO);
	while (width > len)
	{
		write(STDOUT_FILENO, "0", 1);
		arg->written++;
		width--;
	}
	ft_putstr_fd(str, STDOUT_FILENO);
	arg->written += len;
}

static void	ft_print_right_aligned(t_arg *arg, char *str, int len)
{
	int	width;

	width = 0;
	if (arg->part[1])
		width = arg->min_width;
	if (width < 0)
		width *= -1;
	arg->written = 0;
	len += 2;
	while (width > len)
	{
		write(STDOUT_FILENO, " ", 1);
		arg->written++;
		width--;
	}
	arg->written += len;
	ft_putstr_fd("0x", STDOUT_FILENO);
	ft_putstr_fd(str, STDOUT_FILENO);
}

static void	ft_print_left_aligned(t_arg *arg, char *str, int len)
{
	int	width;

	len += 2;
	ft_putstr_fd("0x", STDOUT_FILENO);
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

static void	print_special(char *flag, int len, char *str, t_arg *arg)
{
	char	*str_part;
	int		width;

	arg->written = 0;
	str_part = NULL;
	if (arg->part[2])
	{
		str_part = ft_precision_zeros(str, arg->max_precision, len);
		len = ft_strlen(str_part);
	}
	else
		str_part = ft_strndup(str, len);
	width = arg->min_width;
	if (flag[e_minus])
		ft_print_left_aligned(arg, str_part, len);
	else if (flag[e_zero] && (arg->part[1]) && (width > len))
		ft_print_with_zero(arg, str_part, len);
	else if (arg->part[1] && (arg->min_width < 0))
		ft_print_left_aligned(arg, str_part, len);
	else
		ft_print_right_aligned(arg, str_part, len);
	free(str_part);
	return ;
}

// 64bits computer, so long long and 16 char to write it in hex
void	ft_printf_pointer(t_arg *arg)
{
	unsigned long long	address;
	char				str[(16 + 1)];
	int					len;
	char				*null;

	address = va_arg(arg->args, unsigned long long);
	ft_bzero(str, 17);
	ft_itoa_hex(str, address);
	len = ft_strlen(str);
	null = "0";
	if (!address)
	{
		ft_strlcpy(str, null, 2);
		len = 1;
	}
	if (arg->part[0] || arg->part[1] || arg->part[2])
		print_special(arg->flag, len, str, arg);
	else
	{
		ft_putstr_fd("0x", STDOUT_FILENO);
		ft_putstr_fd(str, STDOUT_FILENO);
		arg->written = len + 2;
	}
	return ;
}
