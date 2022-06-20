/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkasongo <jkasongo@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 17:53:36 by jkasongo          #+#    #+#             */
/*   Updated: 2022/06/15 11:43:52 by jkasongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipelines.h"
#include <readline/readline.h>
#include <errno.h>
#include <string.h>


static char	*get_new_line(void)
{
	char	*line;

	line = NULL;
	rl_on_new_line();
	line = readline("> ");
	return (line);
}
/*
 * Process created to execute the heredoc
 * handle Ctrl-c signal
 * exit with 0
 */
static int	sub_heredoc(t_redirection *redirection, int pipe[])
{
	char	*line;
	size_t	delim_len;
	size_t	line_len;

	ignore_signal_handling();
	close(pipe[0]);
	delim_len = ft_strlen(redirection->filename);
	line = get_new_line();
	while (line != NULL)
	{
		line_len = ft_strlen(line);
		if ((ft_strncmp(line, redirection->filename, line_len) == 0)
			&& (delim_len == line_len))
			break ;
		print_heredoc_lex(line, pipe[1]);
		//write(pipe[1], "\n", 1);
		free(line);
		line = get_new_line();
	}
	if (line)
		free(line);
	close(pipe[1]);
	exit(0);
}

bool	m_heredoc_r(t_redirection *redirection, t_shell *shell, t_command *cmd)
{
	pid_t	pid;
	int		status;
	int		heredoc_fd[2];

	pipe(heredoc_fd);
	ignore_signal_handling();
	pid = fork();
	if (pid == -1)
	{
		set_shell_error(shell, ft_strdup(strerror(errno)), 1);
		return (false);
	}
	if (pid == 0)
		sub_heredoc(redirection, heredoc_fd);
	else
	{
		close(heredoc_fd[1]);
		waitpid(pid, &status, 0);
		if (cmd->fd[0] != STDIN_FILENO)
			close(cmd->fd[0]);
		cmd->fd[0] = heredoc_fd[0];
		if (WIFEXITED(status) && WEXITSTATUS(status) == SIGINT)
			return (false);
	}
	return (true);
}

int	build_all_cmd_redirections(t_shell *shell, t_command *command)
{
	int	status;

	status = 0;
	while (command)
	{
		if (command->redirections)
			status = build_cmd_redirections(shell, command);
		if (status == 1)
			return (1);
		command = command->pipe;
	}
	return (status);
}
