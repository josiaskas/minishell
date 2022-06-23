/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkasongo <jkasongo@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 21:53:36 by jkasongo          #+#    #+#             */
/*   Updated: 2022/06/20 17:46:21 by jkasongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtins.h"
#include "../../includes/pipelines.h"
#include <stdio.h>

static int	print_in_tty(char **args, int fd, size_t len)
{
	size_t	i;
	bool	with_end;

	with_end = true;
	i = 0;
	if (!args)
		return (0);
	if ((ft_strncmp(args[0], "-n", 2) == 0) && (ft_strlen(args[0]) == 2))
	{
		with_end = false;
		i = 1;
	}
	while (i < len)
	{
		if ((i > 0 && with_end) || (i > 1 && !with_end))
			ft_putstr_fd(" ", fd);
		ft_putstr_fd(args[i], fd);
		free(args[i]);
		i++;
	}
	if (with_end)
		write(fd, "\n", 1);
	return (0);
}

static int	print_in_file(char **args, int fd, size_t len)
{
	size_t	i;
	bool	with_end;

	with_end = true;
	i = 0;
	if (!args)
		return (0);
	if ((ft_strncmp(args[0], "-n", 2) == 0) && (ft_strlen(args[0]) == 2))
	{
		with_end = false;
		i = 1;
	}
	while (i < len)
	{
		if ((i > 0 && with_end) || (i > 1 && !with_end))
			ft_putstr_fd(" ", fd);
		ft_putstr_fd(args[i], fd);
		free(args[i]);
		i++;
	}
	if (with_end)
		write(fd, "\n", 1);
	return (0);
}

void	*get_simple_args(void	*data, int index)
{
	char	*text;

	text = ft_strdup((char *)data);
	(void)index;
	return (text);
}

int	echo_builtin_cmd(t_shell *shell, t_command *cmd)
{
	char	**args;
	size_t	i;

	i = 0;
	args = NULL;
	if (cmd->arguments)
	{
		args = (char **)ft_map(cmd->arguments, get_simple_args);
		i = cmd->arguments->length;
	}
	if (isatty(cmd->fd[1]))
		print_in_tty(args, cmd->fd[1], i);
	else
		print_in_file(args, cmd->fd[1], i);
	if (args)
		free(args);
	g_shell.status = 0;
	shell->status = 0;
	if (cmd->fd[0] != STDIN_FILENO)
		close (cmd->fd[0]);
	if (cmd->fd[1] != STDOUT_FILENO)
		close (cmd->fd[1]);
	return (0);
}
