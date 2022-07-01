/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkasongo <jkasongo@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 12:38:36 by jkasongo          #+#    #+#             */
/*   Updated: 2022/06/30 19:59:21 by jkasongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipelines.h"
#include <sys/stat.h>
#include <errno.h>
#include <string.h>

static void	set_cmd_error_p(t_shell *shell, char *cmd_name, char *msg, int code)
{
	char	*tmp;
	char	*error_msg;

	tmp = ft_strjoin(cmd_name, ": ");
	error_msg = ft_strjoin(tmp, msg);
	free(tmp);
	set_shell_error(shell, error_msg, code);
}

// return malloced char of full working path or set cmd error
static char	*find_cmd_working_path(t_shell *shell, t_command *cmd)
{
	struct stat	buffer;
	char		*tmp;
	char		*full_path;
	size_t		i;

	i = 0;
	while (i++ < g_shell.paths->length)
	{
		full_path = (char *)ft_get_elem(g_shell.paths, i);
		tmp = ft_strjoin(full_path, "/");
		full_path = ft_strjoin(tmp, cmd->cmd);
		free(tmp);
		if (lstat(full_path, &buffer) != 0)
			set_cmd_error_p(shell, cmd->cmd, "command not found", 127);
		else if (S_ISDIR(buffer.st_mode))
		{
			free(full_path);
			set_cmd_error_p(shell, cmd->cmd, strerror(EISDIR), 126);
			return (NULL);
		}
		else
			return (full_path);
		free(full_path);
	}
	return (NULL);
}

static bool	check_cmd_is_in_cwd(t_shell *shell, t_command *cmd)
{
	struct stat	buffer;
	char		*path;

	path = NULL;
	path = ft_strrchr(cmd->cmd, '/');
	if (path && stat(cmd->cmd, &buffer) == 0)
	{
		if (S_ISDIR(buffer.st_mode))
		{
			set_cmd_error_p(shell, cmd->cmd, strerror(EISDIR), 126);
			return (false);
		}
		return (true);
	}
	return (false);
}

char	*get_correct_full_path_cmd(t_shell *shell, t_command *cmd)
{
	char	*path;

	path = NULL;
	if (cmd->cmd)
	{
		if (check_cmd_is_in_cwd(shell, cmd))
			return (ft_strdup(cmd->cmd));
		else if (shell->status == 126)
			return (NULL);
		else if ((ft_strncmp(cmd->cmd, "./", 2) == 0)
				|| (ft_strncmp(cmd->cmd, "../", 3) == 0))
		{
			set_cmd_error_p(shell, cmd->cmd, strerror(ENOENT), 127);
			return (NULL);
		}
		else
		{
			if (g_shell.paths)
				path = find_cmd_working_path(shell, cmd);
		}
	}
	return (path);
}
