/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipelines_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkasongo <jkasongo@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 17:53:19 by jkasongo          #+#    #+#             */
/*   Updated: 2022/06/10 19:28:57 by jkasongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipelines.h"
#include <errno.h>
#include <string.h>

void	set_shell_error(t_shell *parser, char *msg, int code)
{
	free(parser->error_msg);
	parser->error_msg = ft_strdup(msg);
	parser->status = code;
}

//close all pipes (read , write) inside pipes
void	close_all_pipes(int *pipes[], int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
		i++;
	}
}

static void	destroy_shell_data(t_shell *parser)
{
	t_command	*cmd;
	t_command	*tmp;

	cmd = parser->commands_list;
	while (cmd != NULL)
	{
		tmp = cmd;
		cmd = cmd->pipe;
		free(tmp->cmd);
		free(tmp->error_msg);
		if (tmp->redirections)
			destroy_redirections(tmp->redirections);
		if (tmp->arguments)
			ft_free_d_array(tmp->arguments);
		free(tmp);
	}
	free(parser->error_msg);
}

/*
 * take parser result and makes redirection, pipes and fork for execution
 * return a code and set g_shell.status
 */
int	run_pipeline(t_shell *parser)
{
	int	code;

	if (parser->syntax_error)
	{
		ft_putstr_fd(parser->error_msg, STDERR_FILENO);
		g_shell.status = 258;
		destroy_shell_data(parser);
		return (258);
	}
	code = make_pipeline(parser);
	if (parser->error_msg && (code != 0))
		ft_putstr_fd(parser->error_msg, STDERR_FILENO);
	destroy_shell_data(parser);
	return (code);
}
