/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environement.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkasongo <jkasongo@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 13:45:21 by jkasongo          #+#    #+#             */
/*   Updated: 2022/04/18 18:14:44 by jkasongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "status.h"
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

static void set_env_pwd()
{
    char        *path;
    char        *buffer;

    buffer = NULL;
    path = NULL;
    buffer = (char *)malloc(1024);
    if(buffer)
    {
        path = getcwd(buffer, 1024);
        if (!path)
            g_shell.error_msg = strerror(errno);
    }
    if (path)
        g_shell.pwd = path;
}

void	ft_create_environ(char *envp[])
{
	t_array *env;
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

void	delete_environ()
{
	t_array	*env;
	t_array	*paths;

	env = g_shell.env;
	paths = g_shell.paths;
	ft_free_dic(env);
	ft_free_d_array(paths);
    free(g_shell.pwd);
}

