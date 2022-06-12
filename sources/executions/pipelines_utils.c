/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipelines_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkasongo <jkasongo@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 17:53:19 by jkasongo          #+#    #+#             */
/*   Updated: 2022/06/10 19:28:57 by jkasongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipelines.h"
#include <errno.h>
#include <string.h>

void	set_shell_error(t_shell *parser, char *msg, int code)
{
	free(parser->error_msg);
	parser->error_msg = ft_strdup(msg);
	parser->status = code;
}

//close all pipes (read , write) inside pipes
void	close_all_pipes(int *pipes[], int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
		i++;
	}
}

void	destroy_shell_data(t_shell *shell)
{
	t_command	*cmd;
	t_command	*tmp;

	cmd = shell->commands_list;
	while (cmd != NULL)
	{
		tmp = cmd;
		cmd = cmd->pipe;
		if (tmp->cmd)
			free(tmp->cmd);
		if (tmp->error_msg)
			free(tmp->error_msg);
		if (tmp->redirections)
			destroy_redirections(tmp->redirections);
		if (tmp->arguments)
			ft_free_d_array(tmp->arguments);
		free(tmp);
	}
	if (shell->error_msg)
		free(shell->error_msg);
}

// set the length of piped command
void	set_len_of_piped_command(t_shell *shell)
{
	int			len;
	t_command	*command;

	if (!shell)
		return ;
	len = 0;
	command = shell->commands_list;
	while (command)
	{
		command = command->pipe;
		len++;
	}
	shell->pipes_len = len;
}
/*
 * Exit sub shell by cleaning memory and set exit code;
 */
void	exit_subshell_cmd(t_shell *shell, t_command *command)
{
	if ((shell->error_msg) && (shell->status != 0))
	{
		if (command->cmd)
		{
			ft_putstr_fd(command->cmd, STDERR_FILENO);
			ft_putstr_fd(" : ", STDERR_FILENO);
		}
		ft_putendl_fd(shell->error_msg, STDERR_FILENO);
	}
	g_shell.status = shell->status;
	destroy_shell_data(shell);
	delete_environ();
	exit(g_shell.status);
}