/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkasongo <jkasongo@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 21:53:36 by jkasongo          #+#    #+#             */
/*   Updated: 2022/06/25 16:36:17 by jkasongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtins.h"
#include "../../includes/minishell.h"

static void	print_unset_error(t_shell *shell, char *identifier)
{
	char	*tmp;
	char	*error_msg;

	tmp = ft_strjoin("minishell: unset: `", identifier);
	error_msg = ft_strjoin(tmp, "': not a valid identifier");
	free(tmp);
	ft_putendl_fd(error_msg, STDERR_FILENO);
	shell->status = 1;
}

static void	unset_found_dic_entry(size_t i)
{
	t_dic_node	*dic;

	dic = (t_dic_node *)ft_del_elem(g_shell.env, i);
	if (ft_strncmp("PATH", dic->key, 5) == 0)
	{
		if (g_shell.paths)
			ft_free_d_array(g_shell.paths);
		g_shell.paths = ft_new_array();
	}
	free(dic->content);
	free(dic->key);
	free(dic);
}

void	find_and_unset(char *var_name)
{
	t_dic_node	*dic;
	size_t		i;
	size_t		len;
	char		*key;

	i = 0;
	len = ft_strlen(var_name);
	while ((i < g_shell.env->length) && (len))
	{
		dic = (t_dic_node *)ft_get_elem(g_shell.env, i);
		key = dic->key;
		if ((ft_strncmp(key, var_name, len) == 0) && (len == ft_strlen(key)))
		{
			if ((ft_strncmp(key, "_", len) == 0) && (len == 1))
				break ;
			else
			{
				unset_found_dic_entry(i);
				break ;
			}
		}
		i++;
	}
}

int	unset_cmd_builtin(t_shell *shell, t_command *cmd)
{
	char	*arg;
	size_t	i;

	i = 0;
	shell->status = 0;
	g_shell.status = 0;
	if (cmd->arguments)
	{
		while (i < cmd->arguments->length)
		{
			arg = NULL;
			arg = (char *)ft_get_elem(cmd->arguments, i);
			if (is_valid_varname_id(arg))
				find_and_unset(arg);
			else
				print_unset_error(shell, arg);
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
