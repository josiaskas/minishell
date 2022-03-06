/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_solve_unsigned.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkasongo <jkasongo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/04 20:51:04 by jkasongo          #+#    #+#             */
/*   Updated: 2021/06/19 06:42:47 by jkasongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static void	print_special(char *flag, char *str, t_arg *arg)
{
	char	*str_precised;
	int		len;

	arg->written = 0;
	str_precised = NULL;
	len = ft_strlen(str);
	if (arg->part[2] && (arg->max_precision > len))
		str_precised = ft_precision_zeros(str, arg->max_precision, len);
	else if ((str[0] == '0') && (arg->part[2] && arg->max_precision == 0))
		str_precised = ft_strdup("");
	else
		str_precised = ft_strdup(str);
	len = ft_strlen(str_precised);
	if (flag[e_minus])
		ft_print_left_aligned_str(arg, str_precised, len);
	else if (flag[e_zero] && (!arg->part[2]) && (arg->min_width > 0))
		ft_print_with_zero_str(arg, str_precised, len);
	else if (arg->part[1] && (arg->min_width < 0))
		ft_print_left_aligned_str(arg, str_precised, len);
	else
		ft_print_right_aligned_str(arg, str_precised, len);
	free(str_precised);
}

void	ft_printf_unsigned(t_arg *arg)
{
	long	nbr;
	char	*str;
	int		len;

	nbr = (long)va_arg(arg->args, unsigned int);
	str = ft_itoa_printf(nbr);
	len = ft_strlen(str);
	if (arg->part[0] || arg->part[1] || arg->part[2])
		print_special(arg->flag, str, arg);
	else
	{
		ft_putstr_fd(str, STDOUT_FILENO);
		arg->written = len;
	}
	free(str);
	return ;
}
