/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkasongo <jkasongo@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 21:53:36 by jkasongo          #+#    #+#             */
/*   Updated: 2022/06/20 17:45:52 by jkasongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtins.h"
#include "../../includes/pipelines.h"

void	ft_print_env_variables(t_command *cmd)
{
	char	**envs;
	size_t	i;

	envs = NULL;
	envs = get_env_array(cmd);
	i = 0;
	if (envs)
	{
		while (envs[i])
		{
			ft_putendl_fd(envs[i], cmd->fd[1]);
			i++;
		}
		ft_free_splitted(envs);
	}
}

int	env_builtin_cmd(t_shell *shell, t_command *cmd)
{
	ft_print_env_variables(cmd);
	g_shell.status = 0;
	shell->status = 0;
	if (cmd->fd[0] != STDIN_FILENO)
		close (cmd->fd[0]);
	if (cmd->fd[1] != STDOUT_FILENO)
		close (cmd->fd[1]);
	return (0);
}
