/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkasongo <jkasongo@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 12:38:36 by jkasongo          #+#    #+#             */
/*   Updated: 2022/06/30 12:39:22 by jkasongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipelines.h"
#include <sys/stat.h>
#include <errno.h>
#include <string.h>

static void	set_cmd_error_p(t_shell *shell, char *cmd_name, char *msg)
{
	char	*tmp;
	char	*error_msg;

	tmp = ft_strjoin(cmd_name, ": ");
	error_msg = ft_strjoin(tmp, msg);
	free(tmp);
	set_shell_error(shell, error_msg, 1);
}

static char	*find_working_path(t_shell *shell, t_command *cmd)
{
	struct stat	buffer;
	char		*tmp;
	char		*full_path;
	size_t		i;

	i = 0;
	while (i < g_shell.paths->length)
	{
		full_path = (char *)ft_get_elem(g_shell.paths, i);
		tmp = ft_strjoin(full_path, "/");
		free(full_path);
		full_path = ft_strjoin(tmp, cmd->cmd);
		free(tmp);
		if (stat(full_path, &buffer) != 0)
			set_cmd_error_p(shell, cmd->cmd, strerror(errno));
		else if (S_ISDIR(buffer.st_mode))
		{
			errno = EISDIR;
			set_cmd_error_p(shell, cmd->cmd, strerror(errno));
		}
		else
			return (full_path);
		free(full_path);
		i++;
	}
	return (NULL);
}

static bool	is_in_cwd(t_shell *shell, t_command *cmd)
{
	struct stat	buffer;
	char		*path;

	path = NULL;
	path = ft_strrchr(cmd, '/');
	if (path && stat(cmd, &buffer) == 0)
	{
		if (S_ISDIR(buffer.st_mode))
		{
			set_cmd_error_p(shell, cmd->cmd, strerror(EISDIR));
			return (false);
		}
		return (true);
	}
	return (false);
}