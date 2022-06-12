/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkasongo <jkasongo@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 21:53:36 by jkasongo          #+#    #+#             */
/*   Updated: 2022/06/11 21:53:38 by jkasongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtins.h"

int	cd_builtin_cmd(t_shell *shell, t_command *cmd)
{
	(void)shell;
	ft_putendl_fd("hello i'm home made CD command\n", cmd->fd[1]);
	shell->status = 0;
	if(cmd->fd[0] != STDIN_FILENO)
		close (cmd->fd[0]);
	if(cmd->fd[1] != STDOUT_FILENO)
		close (cmd->fd[1]);
	return (0);
}

