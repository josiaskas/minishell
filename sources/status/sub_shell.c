/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sub_shell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkasongo <jkasongo@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 13:45:21 by jkasongo          #+#    #+#             */
/*   Updated: 2022/06/10 19:38:37 by jkasongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/status.h"
#include "../../includes/pipelines.h"
#include <sys/wait.h>

void	init_shell_jobs_capability()
{
	t_shell_jobs	*jobs;

	jobs = (t_shell_jobs *)ft_calloc(1, sizeof(t_shell_jobs));
	jobs->jobs = ft_new_array();
	g_shell.jobs = jobs;
}

void	add_stopped_job(t_command *command, int group)
{
	t_shell_job	*job;

	job = ft_calloc(1, sizeof(t_shell_job));
	if (job)
	{
		job->cmd_name = ft_strdup(command->cmd);
		if (command->arguments)
		{
			job->args = (char **)ft_map(command->arguments, map_ret_content);
			job->len_arg = command->arguments->length;
		}
		job->pid = command->id;
		job->group_id = group;
	}
}

void	check_and_destroy_continued_jobs(t_command *command)
{
	size_t		i;
	t_shell_job	*job;

	i = 0;
	if (g_shell.jobs->jobs->length)
	{
		job = (t_shell_job *)ft_get_elem(g_shell.jobs->jobs, i);
		while (job)
		{
			if (job->pid == command->id)
			{
				job = ft_del_elem(g_shell.jobs->jobs, i);
				if (job->cmd_name)
					free(job->cmd_name);
				if (job->args)
					free_array((void **)job->args, job->len_arg);
				free(job);
			}
			i++;
			job = (t_shell_job *)ft_get_elem(g_shell.jobs->jobs, i);
		}
	}
}

static int		get_max_job_group_number()
{
	int			groups;
	size_t		i;
	t_shell_job	*job;

	groups = 1;
	i = 0;
	if (g_shell.jobs->jobs->length)
	{
		job = (t_shell_job *)ft_get_elem(g_shell.jobs->jobs, i);
		while (job)
		{
			if (job->group_id >= groups)
				groups = job->group_id + 1;
			i++;
			job = (t_shell_job *)ft_get_elem(g_shell.jobs->jobs, i);
		}
	}
	return (groups);
}

int	get_sub_shell_last_cmd_status(t_command *commands)
{
	int		status;
	int		group;

	group = get_max_job_group_number();
	while (commands)
	{
		if (WIFSIGNALED(commands->status)
			&& (WTERMSIG(commands->status) == SIGSTOP))
		{
			add_stopped_job(commands, group);
			g_shell.jobs->last_stopped = group;
		}
		if (WIFSIGNALED(commands->status))
			status = WTERMSIG(commands->status);
		else if (WIFEXITED(commands->status))
			status = WEXITSTATUS(commands->status);
		else
			status = 1;
		ft_printf("%s : exit with status code %d\n", commands->cmd, status);
		commands = commands->pipe;
	}
	return (status);
}