/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkasongo <jkasongo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/23 13:18:08 by jkasongo          #+#    #+#             */
/*   Updated: 2021/08/07 22:17:40 by jkasongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <stdarg.h>
# include "../libft.h"

typedef struct s_arg
{
	const char	*format;
	int			cursor;
	int			cursor_arg;
	int			part[4];
	char		flag[4];
	int			min_width;
	int			max_precision;
	char		arg_type;
	int			written;
	va_list		args;
}	t_arg;

enum	e_flags
{
	e_minus,
	e_zero,
	e_space,
	e_plus,
};

int		ft_printf(const char *format, ...);
void	ft_parse_flag(t_arg *arg);
void	ft_parse_width(t_arg *arg);
void	ft_parse_precision(t_arg *arg);
void	ft_parse_arg_type(t_arg *arg);
void	ft_write_arg_data(t_arg *arg);
void	ft_printf_char(t_arg *arg);
void	ft_printf_str(t_arg *arg);
void	ft_printf_pointer(t_arg *arg);
void	ft_printf_int(t_arg *arg);
void	ft_printf_unsigned(t_arg *arg);
void	ft_printf_hexadecimal(t_arg *arg);
void	ft_printf_pourcentage(t_arg *arg);

void	ft_print_with_zero_str(t_arg *arg, char *str, int len);
void	ft_print_right_aligned_str(t_arg *arg, char *str, int len);
void	ft_print_left_aligned_str(t_arg *arg, char *str, int len);

char	*ft_precision_spaces(char *str, int precision, int len, t_arg *arg);
char	*ft_precision_zeros(char *str, int precision, int len);
void	ft_itoa_hex(char *str, unsigned long long nbr);
char	*ft_itoa_printf(long n);
#endif
