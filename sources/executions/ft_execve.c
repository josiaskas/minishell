/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execve.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkasongo <jkasongo@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 17:53:36 by jkasongo          #+#    #+#             */
/*   Updated: 2022/06/15 11:43:42 by jkasongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipelines.h"
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

static void	set_cmd_error(t_shell *shell, char *cmd_name, char *msg)
{
	char	*tmp;
	char	*error_msg;

	tmp = ft_strjoin(cmd_name, ": ");
	error_msg = ft_strjoin(tmp, msg);
	free(tmp);
	set_shell_error(shell, error_msg, 1);
}

// try to run the command

/*
 * Build args and env and try to run the command if command name exist
 * Return 1 (most of the time, failed to open the program)
 * Return 0 if no command name (redirections only type)
 */
int	ft_execve(t_shell *shell, t_command *cmd)
{
	char	**args;
	char	**env;
	char	*full_path;

	args = NULL;
	env = NULL;
	if (ft_strlen(cmd->cmd))
		full_path = get_correct_full_path_cmd(shell, cmd);
	else
		full_path = ft_strdup(cmd->cmd);
	if (!full_path)
		return (shell->status);
	if (cmd->cmd)
	{
		args = get_args_array(cmd);
		env = get_env_array(cmd);
		execve(full_path, args, env);
		ft_free_splitted(args);
		ft_free_splitted(env);
		if (full_path)
			free(full_path);
		set_cmd_error(shell, cmd->cmd, "command not found");
		return (127);
	}
	return (0);
}
