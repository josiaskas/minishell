/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkasongo <jkasongo@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 17:53:36 by jkasongo          #+#    #+#             */
/*   Updated: 2022/06/11 17:53:38 by jkasongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipelines.h"
#include <errno.h>
#include <string.h>

void	print_cmd_error(char *cmd_name, char *error_msg)
{
	if (cmd_name)
	{
		ft_putstr_fd(cmd_name, STDERR_FILENO);
	}
	write(STDERR_FILENO, ": ", 3);
	ft_putendl_fd(error_msg, STDERR_FILENO);
}

void	*map_ret_content(void *content, int index)
{
	(void)index;
	return content;
}

void	*map_join_key_content(void *content, char *key, size_t index)
{
	char	*word;
	char	*temp;

	(void)index;
	temp = ft_strjoin(key, "=");
	word = ft_strjoin(temp, (char *)content);
	free(temp);
	return word;
}

// try to run the command
static void	ft_execve(char *cmd_name, char **args, char **env)
{
	char	*full_path;
	char	*dir;
	char	*tmp;
	size_t	i;

	full_path = ft_strrchr(cmd_name, '/');
	if (full_path)
		execve(cmd_name, args, env);
	i = 0;
	while (i < g_shell.paths->length)
	{
		if (cmd_name[0] == '/')
			break;
		dir = (char *)ft_get_elem(g_shell.paths, i);
		tmp = ft_strjoin(dir, "/");
		full_path = ft_strjoin(tmp, cmd_name);
		free (tmp);
		execve(full_path, args, env);
		free(full_path);
		i++;
	}
}

/*
 * Build args and env and try to run the command if command name exist
 * Return 1 (most of the time, failed to open the program)
 * Return 0 if no command name (redirections only type)
 */
int	ft_exec_cmd(t_shell *shell, t_command *cmd)
{
	char	*tmp;
	char	*error_msg;
	char	**args;
	char	**env;

	args = NULL;
	env  = NULL;
	if (cmd->cmd)
	{
		args = (char **)ft_map(cmd->arguments, map_ret_content);
		env = (char **)ft_map_d(cmd->env, map_join_key_content);
		ft_execve(cmd->cmd, args, env);
		free_array((void **)args, cmd->arguments->length);
		free_array((void **)env, cmd->env->length);
		tmp  = ft_strjoin(cmd->cmd, ": ");
		error_msg  = ft_strjoin(tmp, strerror(errno));
//		ft_putendl_fd(error_msg, STDOUT_FILENO);
		free(tmp);
		set_shell_error(shell, error_msg, 1);
		return (1);
	}
	return (0);
}
