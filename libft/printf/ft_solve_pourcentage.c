/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_solve_pourcentage.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkasongo <jkasongo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/04 20:51:04 by jkasongo          #+#    #+#             */
/*   Updated: 2021/06/19 06:42:04 by jkasongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void	ft_printf_pourcentage(t_arg *arg)
{
	char	*str;
	char	*str_formated;
	int		len;

	str = "%";
	str_formated = 0;
	if (arg->part[2])
		str_formated = ft_precision_spaces(str, arg->max_precision, 2, arg);
	else
		str_formated = ft_strndup(str, 2);
	len = ft_strlen(str_formated);
	if (arg->flag[e_minus])
		ft_print_left_aligned_str(arg, str_formated, len);
	else if (arg->flag[e_zero])
		ft_print_with_zero_str(arg, str_formated, len);
	else if (arg->part[1] && (arg->min_width < 0))
		ft_print_left_aligned_str(arg, str_formated, len);
	else
		ft_print_right_aligned_str(arg, str_formated, len);
	free(str_formated);
	return ;
}
