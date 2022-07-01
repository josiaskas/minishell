/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkasongo <jkasongo@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 21:53:36 by jkasongo          #+#    #+#             */
/*   Updated: 2022/06/30 19:51:42 by jkasongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtins.h"
#include "../../includes/minishell.h"

static void	make_exit_error(char *arg, char *msg, t_shell *shell)
{
	char	*tmp;
	char	*tmp2;

	tmp = NULL;
	if (arg)
		tmp = ft_strjoin("exit: ", arg);
	else
		tmp = ft_strdup("exit");
	tmp2 = ft_strjoin(": ", msg);
	if (shell->error_msg)
		free(shell->error_msg);
	shell->error_msg = ft_strjoin(tmp, tmp2);
	free(tmp);
	free(tmp2);
}

static int	parse_exit(t_shell *shell, t_command *cmd)
{
	int		status;
	char	*arg;

	arg = NULL;
	status = 0;
	if (cmd->arguments->length)
	{
		arg = (char *)ft_get_elem(cmd->arguments, 0);
		if (!ft_is_a_number(arg))
		{
			make_exit_error(arg, "numeric argument required", shell);
			return (255);
		}
		else if (cmd->arguments->length > 1)
		{
			make_exit_error(NULL, "too many arguments", shell);
			return (1);
		}
		status = ft_atoi(arg);
		status = status % 256;
	}
	return (status);
}

int	exit_builtin_cmd(t_shell *shell, t_command *cmd)
{
	int		status;

	if (shell->error_msg)
		free(shell->error_msg);
	shell->error_msg = NULL;
	shell->status = 0;
	if (cmd->arguments)
	{
		status = parse_exit(shell, cmd);
		shell->status = status;
		g_shell.status = status;
	}
	else
		status = g_shell.status;
	if (cmd->fd[0] != STDIN_FILENO)
		close (cmd->fd[0]);
	if (cmd->fd[1] != STDOUT_FILENO)
		close (cmd->fd[1]);
	return (status);
}
