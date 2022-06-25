/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkasongo <jkasongo@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 21:53:36 by jkasongo          #+#    #+#             */
/*   Updated: 2022/06/25 16:35:43 by jkasongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtins.h"
#include "../../includes/pipelines.h"
#include <errno.h>
#include <string.h>

static void	set_cd_error(t_shell *shell, char *path, char *msg)
{
	char	*tmp;
	char	*error_msg;

	ft_putstr_fd("cd: ", STDERR_FILENO);
	tmp = ft_strjoin(path, ": ");
	error_msg = ft_strjoin(tmp, msg);
	free(tmp);
	ft_putendl_fd(error_msg, STDERR_FILENO);
	set_shell_error(shell, error_msg, 1);
}

static void	set_to_home_dir(t_shell *shell)
{
	t_dic_node	*dic;
	char		*path;

	dic = ft_elem_dic(g_shell.env, "HOME");
	if (dic)
	{
		path = (char *)dic->content;
		if (chdir(path) != 0)
			set_cd_error(shell, path, strerror(errno));
		else
			set_env_pwd(shell);
	}
}

int	cd_builtin_cmd(t_shell *shell, t_command *cmd)
{
	char	*path;

	shell->status = 0;
	g_shell.status = 0;
	if (cmd->arguments)
	{
		path = ft_get_elem(cmd->arguments, 0);
		if (path)
		{
			if (chdir(path) != 0)
				set_cd_error(shell, path, strerror(errno));
			else
				set_env_pwd(shell);
		}
	}
	else
		set_to_home_dir(shell);
	g_shell.status = shell->status;
	if (cmd->fd[0] != STDIN_FILENO)
		close (cmd->fd[0]);
	if (cmd->fd[1] != STDOUT_FILENO)
		close (cmd->fd[1]);
	return (0);
}
