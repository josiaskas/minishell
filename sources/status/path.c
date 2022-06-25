/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkasongo <jkasongo@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 21:12:33 by jkasongo          #+#    #+#             */
/*   Updated: 2022/06/22 18:20:41 by jkasongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/status.h"
#include "../../includes/pipelines.h"
#include <errno.h>
#include <string.h>

static void	set_getcwd_error(t_shell *shell, char *msg)
{
	char	*error_msg;

	error_msg = ft_strjoin("getcwd: ", msg);
	if (shell)
		set_shell_error(shell, error_msg, 1);
	else
	{
		if (g_shell.error_msg)
			free(g_shell.error_msg);
		g_shell.error_msg = error_msg;
	}
}

static char	*try_to_get_cwd(t_shell *shell)
{
	char		*path;
	char		*buffer;

	path = NULL;
	buffer = (char *)ft_calloc(1, 2048);
	path = getcwd(buffer, 2048);
	if (!ft_strlen(path))
	{
		free(buffer);
		buffer = NULL;
		set_getcwd_error(shell, strerror(errno));
		path = NULL;
	}
	return (path);
}

void	set_env_pwd(t_shell *shell)
{
	char		*path;
	t_dic_node	*dic;

	path = try_to_get_cwd(shell);
	if (path)
	{
		if (g_shell.pwd)
			free(g_shell.pwd);
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
}