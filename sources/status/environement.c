/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environement.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkasongo <jkasongo@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 13:45:21 by jkasongo          #+#    #+#             */
/*   Updated: 2022/06/22 18:20:33 by jkasongo         ###   ########.fr       */
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

void	set_env_pwd(void)
{
	char		*path;
	char		*buffer;
	t_dic_node	*dic;

	path = NULL;
	buffer = (char *)ft_calloc(1, 2048);
	if (buffer)
	{
		path = getcwd(buffer, 2048);
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
		ft_push_to_dic(g_shell.env, ft_strdup("PWD"), ft_strdup(g_shell.pwd));
}

void	ft_make_env_table(char *envp[])
{
	t_array	*env;
	char	*value;
	char	*var_name;
	size_t	i;

	env = ft_new_dic();
	g_shell.env = env;
	if (!env || !envp)
		return ;
	i = 0;
	while (envp[i] != 0)
	{
		value = ft_strchr(envp[i], '=');
		if (value && (value > envp[i]))
		{

			var_name = ft_calloc(1, (value - envp[i]) + 1);
			ft_strlcpy(var_name, envp[i], (value - envp[i]) + 1);
			value = ft_strdup((value + 1));
			ft_push_to_dic(env, var_name, value);
			if (ft_strncmp("PATH", var_name, 5) == 0)
				make_paths(value);
		}
		i++;
	}
}

void	ft_create_environ(char *envp[])
{
	t_dic_node	*dic;
	int			level;

	level = 1;
	ft_make_env_table(envp);
	g_shell.error_msg = NULL;
	if (!g_shell.paths)
		make_paths(NULL);
	set_env_pwd();
	dic = ft_elem_dic(g_shell.env, "SHLVL");
	if (dic)
	{
		level = ft_atoi((char *)dic->content);
		if (dic->content)
			free (dic->content);
		dic->content = ft_itoa((level + 1));
	}
	else
		ft_push_to_dic(g_shell.env, ft_strdup("SHLVL"), ft_itoa(1));
}

void	delete_environ(void)
{
	t_array			*env;
	t_array			*paths;

	env = g_shell.env;
	paths = g_shell.paths;
	ft_free_dic(env);
	ft_free_d_array(paths);
	free(g_shell.pwd);
	if (g_shell.error_msg)
		free(g_shell.error_msg);
}
