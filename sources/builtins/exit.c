/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkasongo <jkasongo@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 21:53:36 by jkasongo          #+#    #+#             */
/*   Updated: 2022/06/11 21:53:38 by jkasongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtins.h"
#include "../../includes/minishell.h"

int	exit_builtin_cmd(t_shell *shell, t_command *cmd)
{
	int		status;
	char	*arg;

	arg = NULL;
	status = g_shell.status;
	if (shell->error_msg)
		free(shell->error_msg);
	shell->error_msg = NULL;
	if (cmd->arguments)
	{
		arg = (char *)ft_get_elem(cmd->arguments, 0);
		status = ft_atoi(arg);
		status = status % 256;
	}
	shell->status = status;
	g_shell.status = status;
	if(cmd->fd[0] != STDIN_FILENO)
		close (cmd->fd[0]);
	if(cmd->fd[1] != STDOUT_FILENO)
		close (cmd->fd[1]);
	return (status);
}