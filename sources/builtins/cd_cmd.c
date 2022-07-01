/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkasongo <jkasongo@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 21:53:36 by jkasongo          #+#    #+#             */
/*   Updated: 2022/06/30 20:03:28 by jkasongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtins.h"
#include "../../includes/minishell.h"
#include <errno.h>
#include <string.h>

static void	set_cd_error(t_shell *shell, char *path, char *msg)
{
	char	*tmp;
	char	*tmp2;

	tmp = ft_strjoin("cd: ", path);
	tmp2 = ft_strjoin(": ", msg);
	if (shell->error_msg)
		free(shell->error_msg);
	shell->error_msg = ft_strjoin(tmp, tmp2);
	shell->status = 1;
	free(tmp);
	free(tmp2);
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
	if (shell->error_msg)
		free(shell->error_msg);
	shell->error_msg = NULL;
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
	return (shell->status);
}
