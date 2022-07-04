/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_suite.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkasongo <jkasongo@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 16:31:29 by jkasongo          #+#    #+#             */
/*   Updated: 2022/07/04 16:40:43 by jkasongo         ###   ########.fr       */
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

static void	set_heredoc_process_signal(void)
{
	setup_signal(SIGINT, SIG_DFL);
	setup_signal(SIGQUIT, SIG_IGN);
}

/*
 * Process created to execute the heredoc
 * handle Ctrl-c signal
 * exit with 0
 */
static int	sub_h(t_shell *shell, t_redirection *red, int pipe[], int *pipes[])
{
	char	*line;
	size_t	delim_len;
	size_t	line_len;

	set_heredoc_process_signal();
	close(pipe[0]);
	delim_len = ft_strlen(red->filename);
	line = get_new_line();
	while (line != NULL)
	{
		line_len = ft_strlen(line);
		if ((ft_strncmp(line, red->filename, line_len) == 0)
			&& (delim_len == line_len))
			break ;
		print_heredoc_lex(line, pipe[1]);
		free(line);
		line = get_new_line();
	}
	if (line)
		free(line);
	close(pipe[1]);
	close_all_pipes(pipes, shell->pipes_len);
	destroy_shell_data(shell);
	delete_environ();
	exit(0);
}

// redirection, shell, cmd, pipes
bool	m_here_r(t_redirection *red, t_shell *shell, t_command *cmd, int *pi[])
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
		sub_h(shell, red, heredoc_fd, pi);
	else
	{
		close(heredoc_fd[1]);
		waitpid(pid, &status, 0);
		if (cmd->fd[0] != STDIN_FILENO)
			close(cmd->fd[0]);
		cmd->fd[0] = heredoc_fd[0];
		if (WIFSIGNALED(status))
			return (false);
	}
	return (true);
}
