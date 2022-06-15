/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipelines.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkasongo <jkasongo@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 14:52:09 by jkasongo          #+#    #+#             */
/*   Updated: 2022/06/15 11:46:50 by jkasongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipelines.h"
#include <errno.h>
#include <string.h>

/*
 * Allocate enough space and make pipes
 * Return 1 if failed and set error via set_shell_error
 */
static int	**build_pipes(t_shell *shell)
{
	int	**pipes;
	int	i;
	int	len;

	i = 0;
	len = shell->pipes_len;
	pipes = (int **)ft_calloc(len, sizeof(int *));
	while ((i < len) && (pipes))
	{
		pipes[i] = (int *)ft_calloc(2, sizeof(int));
		if (pipe(pipes[i]) == -1)
		{
			set_shell_error(shell, ft_strdup(strerror(errno)), 1);
			break ;
		}
		i++;
	}
	return (pipes);
}

/*
 * Assign the correct pipe to the command
 * Return 0 after assignement
 * Return 1 if pipes_made == NULL or cmd = NULL
 */
static int	assign_pipes(int *pipes_made[], t_command *cmd, int pipes_len)
{
	int	data_pipes[2];
	int	i;

	i = 0;
	if (!cmd || !pipes_made)
		return (1);
	while (i < pipes_len)
	{
		data_pipes[0] = pipes_made[i][0];
		data_pipes[1] = pipes_made[i][1];
		if (i == 0)
			data_pipes[0] = STDIN_FILENO;
		if ((i + 1) < (pipes_len))
			data_pipes[1] = pipes_made[i + 1][1];
		if (i == (pipes_len - 1))
			data_pipes[1] = STDOUT_FILENO;
		cmd->fd[0] = data_pipes[0];
		cmd->fd[1] = data_pipes[1];
		cmd = cmd->pipe;
		i++;
	}
	return (0);
}

/*
 * Close all pipes and start execution of command inside the new process
 * Return 1 if failed (no exec or error)
 */
static void	exec_subshell(t_shell *shell, t_command *command, int *pipes[])
{
	if (command->fd[0] != 0)
		dup2(command->fd[0], STDIN_FILENO);
	if (command->fd[1] != 1)
		dup2(command->fd[1], STDOUT_FILENO);
	close_all_pipes(pipes, shell->pipes_len);
	free_array((void **)pipes, shell->pipes_len);
	command->fd[0] = STDIN_FILENO;
	command->fd[1] = STDOUT_FILENO;
	command->state = e_cmd_running;
	command->shell_level++;
	command->env = g_shell.env;
	shell->status = 0;
	if (shell->error_msg)
		free(shell->error_msg);
	shell->error_msg = NULL;
	shell->is_parent = false;
	shell->status = execute_cmd(shell, command);
	exit_subshell_cmd(shell, command);
}

/*
 * Create sub shell proces and make them run
 * return 0 for parent if everything perfect
 * Return 1  or error code if child failed or parent failed to make fork
 */
static int	make_sub_shell(t_shell *shell, t_command *command, int *pipes[])
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		set_shell_error(shell, ft_strdup(strerror(errno)), 1);
		return (1);
	}
	if (pid == 0)
	{
		exec_subshell(shell, command, pipes);
		return (1);
	}
	command->id = pid;
	shell->is_parent = true;
	command->state = e_cmd_waiting;
	return (0);
}

/*
*  Make pipelines, aka as fork each command and makes pipes
*  return 1 if failed to make pipes or fork
*/
int	make_pipeline(t_shell *shell, t_command	*cmd)
{
	int			**pipes;
	int			i;

	pipes = build_pipes(shell);
	if (shell->status != 0)
		return (1);
	if (assign_pipes(pipes, cmd, shell->pipes_len) != 0)
		return (1);
	i = 0;
	while (i < shell->pipes_len)
	{
		if (make_sub_shell(shell, cmd, pipes) > 0)
			break ;
		cmd = cmd->pipe;
		i++;
	}
	close_all_pipes(pipes, shell->pipes_len);
	free_array((void **)pipes, shell->pipes_len);
	wait_all_child_process(shell);
	g_shell.status = get_sub_shell_last_cmd_status(shell->commands_list);
	return (0);
}
