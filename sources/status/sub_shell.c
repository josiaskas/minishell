/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sub_shell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkasongo <jkasongo@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 13:45:21 by jkasongo          #+#    #+#             */
/*   Updated: 2022/06/15 11:42:09 by jkasongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/status.h"
#include "../../includes/pipelines.h"
#include <sys/wait.h>

/*
 * Get the status of the command that was executed
 * use internal maccros to get the value
 * return 128 + (status) for signaled process
 */
int	get_sub_shell_last_cmd_status(t_command *commands)
{
	int		status;

	while (commands)
	{
		if (WIFSIGNALED(commands->status))
			status = 128 + WTERMSIG(commands->status);
		else if (WIFEXITED(commands->status))
			status = WEXITSTATUS(commands->status);
		else
			status = 1;
		commands = commands->pipe;
	}
	return (status);
}
