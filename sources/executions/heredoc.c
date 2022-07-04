/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkasongo <jkasongo@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 17:53:36 by jkasongo          #+#    #+#             */
/*   Updated: 2022/07/04 16:41:28 by jkasongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipelines.h"

bool	m_here_r(t_redirection *red, t_shell *shell, t_command *cmd, int *pi[]);

static int	build_cmd_h_red(t_shell *shell, t_command *command, int *pipes[])
{
	bool			made;
	size_t			i;
	t_redirection	*redirection;

	made = true;
	i = 0;
	while (i < command->redirections->length)
	{
		redirection = (t_redirection *)ft_get_elem(command->redirections, i);
		if (redirection->type == e_redirection_heredoc)
			made = m_here_r(redirection, shell, command, pipes);
		if (made == false)
			break ;
		i++;
	}
	if (made == false)
		return (1);
	return (0);
}

/*
 * Build only heredocs redirections. must be done first
 * Free pipes "pips" if error found
 */
int	build_all_heredoc_reds(t_shell *shell, t_command *command, int *pips[])
{
	int	status;

	status = 0;
	if (shell->error_msg)
		free(shell->error_msg);
	shell->error_msg = NULL;
	while (command)
	{
		if (command->redirections)
			status = build_cmd_h_red(shell, command, pips);
		if (status == 1)
			break ;
		command = command->pipe;
	}
	if (status == 1 && pips)
	{
		shell->status = 1;
		g_shell.status = 1;
		close_all_pipes(pips, shell->pipes_len);
		free_array((void **)pips, shell->pipes_len);
	}
	return (status);
}
