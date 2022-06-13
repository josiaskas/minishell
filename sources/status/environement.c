/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environement.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkasongo <jkasongo@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 13:45:21 by jkasongo          #+#    #+#             */
/*   Updated: 2022/06/10 19:38:37 by jkasongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/status.h"
#include <errno.h>
#include <string.h>

static void	make_paths(char *path_var)
{
	t_array	*paths;
	char	**list;
	size_t	i;

	paths = ft_new_array();
	i = 0;
	if (paths && path_var)
	{
		list = ft_split(path_var, ':');
		while (list[i] != 0)
		{
			ft_push(paths, list[i]);
			i++;
		}
		free(list);
	}
	g_shell.paths = paths;
}

static void	set_env_pwd(void)
{
	char		*path;
	char		*buffer;
	t_dic_node	*dic;

	path = NULL;
	buffer = (char *)ft_calloc(1, 1024);
	if (buffer)
	{
		path = getcwd(buffer, 1024);
		if (!path)
			g_shell.error_msg = strerror(errno);
	}
	if (path)
		g_shell.pwd = path;
	dic = ft_elem_dic(g_shell.env, "PWD");
	if (dic)
	{
		free (dic->content);
		dic->content = ft_strdup(g_shell.pwd);
	}
	else
		ft_push_to_dic(g_shell.env,"PWD", ft_strdup(g_shell.pwd));
}

void	ft_create_environ(char *envp[])
{
	t_array	*env;
	char	**data;
	size_t	i;

	env = ft_new_dic();
	if (!envp)
		return ;
	i = 0;
	while (envp[i] != 0)
	{
		data = ft_split(envp[i], '=');
		if (data[0] != 0)
		{
			ft_push_to_dic(env, data[0], data[1]);
			if (ft_strncmp("PATH", data[0], 5) == 0)
				make_paths(data[1]);
		}
		free(data);
		i++;
	}
	if (!g_shell.paths)
		make_paths(NULL);
	set_env_pwd();
	g_shell.env = env;
}

void	delete_environ(void)
{
	t_array			*env;
	t_array			*paths;
	t_shell_job		*job;

	env = g_shell.env;
	paths = g_shell.paths;
	ft_free_dic(env);
	ft_free_d_array(paths);
	free(g_shell.pwd);
	if (g_shell.jobs->jobs)
	{
		while(g_shell.jobs->jobs->length)
		{
			job = (t_shell_job *)ft_pop(g_shell.jobs->jobs);
			if (job->cmd_name)
				free(job->cmd_name);
			if (job->args)
				free_array((void **)job->args, job->len_arg);
			free(job);
		}
		ft_free_d_array(g_shell.jobs->jobs);
	}
}


