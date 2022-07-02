/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkasongo <jkasongo@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 21:53:36 by jkasongo          #+#    #+#             */
/*   Updated: 2022/06/30 19:51:16 by jkasongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtins.h"
#include "../../includes/pipelines.h"

static void	set_export_error(t_shell *shell, char *identifier)
{
	char	*tmp;

	tmp = ft_strjoin("export: ", identifier);
	if (shell->error_msg)
		free(shell->error_msg);
	shell->error_msg = ft_strjoin(tmp, ": not a valid identifier");
	shell->status = 1;
	free(tmp);
}

bool	is_valid_varname_id(char *var_name)
{
	size_t	size;
	size_t	i;

	size = ft_strlen(var_name);
	if (size == 0)
		return (false);
	i = 0;
	while (i < size)
	{
		if ((i == 0) && (!ft_isalpha(var_name[i]) && var_name[i] != '_'))
			return (false);
		if ((i > 0) && (!ft_isalnum(var_name[i]) && var_name[i] != '_'))
			return (false);
		i++;
	}
	return (true);
}

static void	add_to_env_data(char *var_name, char *value)
{
	t_dic_node	*dic;
	size_t		len;

	dic = NULL;
	len = ft_strlen(var_name);
	dic = ft_elem_dic(g_shell.env, var_name);
	if ((ft_strncmp(var_name, "_", len) == 0) && len == 1)
	{
		free(value);
		free(var_name);
		free(dic->content);
		dic->content = ft_strdup("_");
		return ;
	}
	if (dic)
	{
		free(dic->content);
		dic->content = value;
	}
	else
		ft_push_to_dic(g_shell.env, var_name, value);
	if ((ft_strncmp("PATH", var_name, 5) == 0) && (ft_strlen(var_name) == 4))
		make_bin_search_paths(value);
}

static int	try_add_env(t_shell *shell, char *arg)
{
	char		*var;
	char		*value;

	value = ft_strchr(arg, '=');
	if (!value)
		return (0);
	var = ft_get_env_varname(arg);
	if (is_valid_varname_id(var))
	{
		if (value)
			value = ft_strdup((value + 1));
		add_to_env_data(var, value);
		return (0);
	}
	set_export_error(shell, arg);
	free(var);
	return (1);
}

int	export_cmd_builtin(t_shell *shell, t_command *cmd)
{
	char	*arg;
	size_t	i;
	int		status;

	i = 0;
	shell->status = 0;
	if (cmd->arguments)
	{
		while (i < cmd->arguments->length)
		{
			arg = (char *)ft_get_elem(cmd->arguments, i);
			status = try_add_env(shell, arg);
			if (status == 1)
				break ;
			i++;
		}
	}
	else
		ft_print_env_variables_with_declare(cmd);
	g_shell.status = shell->status;
	if (cmd->fd[0] != STDIN_FILENO)
		close (cmd->fd[0]);
	if (cmd->fd[1] != STDOUT_FILENO)
		close (cmd->fd[1]);
	return (shell->status);
}
