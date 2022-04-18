/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environement.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkasongo <jkasongo@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 13:45:21 by jkasongo          #+#    #+#             */
/*   Updated: 2022/04/18 18:04:06 by jkasongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "status.h"

static void	make_paths(char *path_var)
{
	t_array	*paths;
	char	**list;
	size_t	i;

	paths = ft_new_array();
	i = 0;
	if (paths)
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

void	ft_create_environ(char *envp[])
{
	t_array	*env;
	char	**data;
	size_t	i;

	env = ft_new_dic();
	i = 0;
	while (envp[i] != 0)
	{
		data = ft_split(envp[i], '=');
		if (data[0] != 0)
		{
			ft_push_to_dic(env, data[0], data[1]);
			if (ft_strncmp("PATH",data[0],5) == 0)
				make_paths(data[1]);
		}
		free(data);
		i++;
	}
	g_shell.env = env;
}

void	delete_environ()
{
	t_array	*env;
	t_array	*paths;

	env = g_shell.env;
	paths = g_shell.paths;
	ft_free_dic(env);
	ft_free_array(paths);
	g_shell.env = 0;
	g_shell.paths = 0;
}

