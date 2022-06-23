/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkasongo <jkasongo@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 21:53:36 by jkasongo          #+#    #+#             */
/*   Updated: 2022/06/22 18:19:22 by jkasongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtins.h"
#include "../../includes/minishell.h"

void	find_and_unset(char *var_name)
{
	t_dic_node	*dic;
	char		*key;
	size_t		i;
	size_t		len;

	i = 0;
	while (i < g_shell.env->length)
	{
		dic = (t_dic_node *)ft_get_elem(g_shell.env, i);
		if (dic == 0)
			break ;
		key = dic->key;
		len = ft_strlen(key);
		if ((ft_strncmp(key, var_name, len) == 0)
			&& (len == ft_strlen(var_name)))
		{
			dic = (t_dic_node *)ft_del_elem(g_shell.env, i);
			free(dic->content);
			free(dic->key);
			free(dic);
			break ;
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
			find_and_unset(arg);
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

