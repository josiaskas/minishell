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
#include "../../includes/minishell.h"

static void	print_grouped_job_paused(int group)
{
	size_t		i;
	t_shell_job	*job;

	i = 0;
	ft_printf("\n[%d]\t", group);
	if (g_shell.jobs->jobs->length)
	{
		job = (t_shell_job *)ft_get_elem(g_shell.jobs->jobs, i);
		while (job)
		{
			if (job->group_id == group)
				ft_printf("\t\t%d suspended %s\n", job->pid, job->cmd_name);
			i++;
			job = (t_shell_job *)ft_get_elem(g_shell.jobs->jobs, i);
		}
	}
}

int	jobs_builtin_cmd(t_shell *shell, t_command *cmd)
{
	size_t		i;
	t_shell_job	*job;
	int			last_printed_group;

	i = 0;
	job = (t_shell_job *)ft_get_elem(g_shell.jobs->jobs, i);
	while (job)
	{
		if (job->group_id != last_printed_group)
		{
			print_grouped_job_paused(job->group_id);
			last_printed_group = job->group_id;
		}
		i++;
		job = (t_shell_job *)ft_get_elem(g_shell.jobs->jobs, i);
	}
	shell->status = 0;
	if(cmd->fd[0] != STDIN_FILENO)
		close (cmd->fd[0]);
	if(cmd->fd[1] != STDOUT_FILENO)
		close (cmd->fd[1]);
	return (0);
}

