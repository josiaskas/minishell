/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environement.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkasongo <jkasongo@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 13:45:21 by jkasongo          #+#    #+#             */
/*   Updated: 2022/06/25 16:38:31 by jkasongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/status.h"
#include "../../includes/builtins.h"

static void	print_shell_init_error(void)
{
	ft_putstr_fd("minishell-init: ", STDERR_FILENO);
	ft_putendl_fd(g_shell.error_msg, STDERR_FILENO);
	free(g_shell.error_msg);
	g_shell.error_msg = NULL;
}

// create the array of bin path
void	make_bin_search_paths(char *path_var)
{
	t_array	*paths;
	char	**list;
	size_t	i;

	if (g_shell.paths)
		ft_free_d_array(g_shell.paths);
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

void	ft_make_env_table(char *envp[])
{
	t_array	*env;
	char	*value;
	char	*var;
	size_t	i;

	env = ft_new_dic();
	g_shell.env = env;
	if (!env || !envp)
		return ;
	i = 0;
	while (ft_strlen(envp[i]))
	{
		var = ft_get_env_varname(envp[i]);
		value = ft_get_env_value_in_line(envp[i]);
		ft_push_to_dic(env, var, value);
		if ((ft_strncmp("PATH", var, 5) == 0) && (ft_strlen(var) == 4))
			make_bin_search_paths(value);
		i++;
	}
}

void	ft_create_environ(char *envp[])
{
	t_dic_node	*dic;
	int			level;

	ft_make_env_table(envp);
	g_shell.error_msg = NULL;
	if (!g_shell.paths)
		make_bin_search_paths(NULL);
	set_env_pwd(NULL);
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
	if (g_shell.error_msg)
		print_shell_init_error();
}

void	delete_environ(void)
{
	ft_free_dic(g_shell.env);
	g_shell.env = NULL;
	if (g_shell.paths)
	{
		ft_free_d_array(g_shell.paths);
		g_shell.paths = NULL;
	}
	if (g_shell.pwd)
		free(g_shell.pwd);
	if (g_shell.error_msg)
		free(g_shell.error_msg);
}
