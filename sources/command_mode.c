/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_mode.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkasongo <jkasongo@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 11:56:51 by jkasongo          #+#    #+#             */
/*   Updated: 2022/06/25 16:33:08 by jkasongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipelines.h"

void	command_mode_script(char *file_path)
{
	ft_putstr_fd(file_path, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putendl_fd("will not be read minishell doesn't treat script", 2);
	g_shell.status = 127;
}

static bool	check_flags(char *flags)
{
	int		flag_count;
	int		count;
	size_t	i;

	count = 0;
	flag_count = 0;
	i = 0;
	while (flags[i] != 0)
	{
		if (flags[i] == '-')
			flag_count++;
		else if (flags[i] != 'c')
		{
			count++;
			break ;
		}
		i++;
	}
	if (flag_count > 1 || count > 0)
		return (false);
	return (true);
}

void	get_flag_command_and_exec(char *flags, char *line)
{
	if (check_flags(flags))
	{
		if (ft_strlen(line) > 0)
			execute_pipeline(parse_shell_line(line));
	}
	else
	{
		ft_putendl_fd("minshell : Usage:\tminishell -c \"line\"", 2);
		g_shell.status = 2;
	}
}
