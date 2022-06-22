/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkasongo <jkasongo@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 21:53:36 by jkasongo          #+#    #+#             */
/*   Updated: 2022/06/22 18:19:08 by jkasongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtins.h"
#include "../../includes/pipelines.h"

static void	set_export_error(t_shell *shell, char *id)
{
	char	*tmp;
	char	*error_msg;

	ft_putstr_fd("export: `", STDERR_FILENO);
	tmp = ft_strjoin(id, "': ");
	error_msg = ft_strjoin(tmp, "not a valid identifier");
	free(tmp);
	ft_putendl_fd(error_msg, STDERR_FILENO);
	set_shell_error(shell, error_msg, 1);
}

static char	*get_varname(char *begin, char *end)
{
	char	*varname;

	varname = (char *) NULL;
	while (begin != end)
	{
		varname = ft_concat_char(varname, begin[0]);
		begin++;
	}
	return (varname);
}

static void	add_element_to_env(char *var_name, char *value)
{
	t_dic_node	*dic;

	dic = ft_elem_dic(g_shell.env, var_name);
	if (dic)
	{
		free (dic->content);
		dic->content = value;
	}
	else
		ft_push_to_dic(g_shell.env, var_name, value);
}

static int	try_add_env(t_shell *shell, char *arg)
{
	char	*var_name;
	char	*value;
	char	*temp;

	temp = ft_strchr(arg, '=');
	if (!temp)
		return (0);
	else if (temp == arg)
	{
		set_export_error(shell, arg);
		return (1);
	}
	else if (temp != arg)
	{
		var_name = get_varname(arg, temp);
		value = ft_strdup((temp + 1));
		add_element_to_env(var_name, value);
		return (0);
	}
	return (0);
}

int	export_cmd_builtin(t_shell *shell, t_command *cmd)
{
	char	*arg;
	size_t	i;
	int		status;

	i= 0;
	shell->status = 0;
	g_shell.status = 0;
	if (cmd->arguments)
	{
		while (i < cmd->arguments->length)
		{
			arg = NULL;
			arg = (char *)ft_get_elem(cmd->arguments, i);
			status = try_add_env(shell, arg);
			if (status == 1)
				break;
			i++;
		}
	}
	g_shell.status = shell->status;
	if (cmd->fd[0] != STDIN_FILENO)
		close (cmd->fd[0]);
	if (cmd->fd[1] != STDOUT_FILENO)
		close (cmd->fd[1]);
	return (0);
}
