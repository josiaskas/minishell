/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkasongo <jkasongo@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 16:16:43 by jkasongo          #+#    #+#             */
/*   Updated: 2022/06/10 19:33:23 by jkasongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipelines.h"
#include <errno.h>
#include <string.h>
#include <fcntl.h>


static void set_redirection_error(t_shell *shell, char *filename, char *msg)
{
	char	*tmp;
	char	*error_msg;

	tmp  = ft_strjoin(filename, ": ");
	error_msg  = ft_strjoin(tmp, msg);
	free(tmp);
	set_shell_error(shell, error_msg, 1);
}

static bool	make_output_redirection(t_redirection *redirection, t_shell *shell)
{
	int		fd;

	if (redirection->type == e_redirection_append_out)
		fd = open(redirection->filename, O_CREAT | O_RDWR | O_APPEND, 0644);
	else
		fd = open(redirection->filename, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd == -1)
	{
		set_redirection_error(shell, redirection->filename, strerror(errno));
		return (false);
	}
	if (shell->is_parent)
	{
		if (shell->commands_list->fd[1] != STDOUT_FILENO)
			close(shell->commands_list->fd[1]);
		shell->commands_list->fd[1] = fd;
	}
	else
	{
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
	return (true);
}

static bool	make_input_redirection(t_redirection *redirection, t_shell *shell)
{
	int		fd;

	fd = open(redirection->filename, O_RDONLY);
	if (fd == -1)
	{
		set_redirection_error(shell, redirection->filename, strerror(errno));
		return (false);
	}
	if (shell->is_parent)
	{
		if (shell->commands_list->fd[0] != STDIN_FILENO)
			close(shell->commands_list->fd[0]);
		shell->commands_list->fd[0] = fd;
	}
	else
	{
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
	return (true);
}

int	build_cmd_redirections(t_shell *shell, t_command *command)
{
	bool			made;
    size_t          i;
    t_redirection   *redirection;

	made = false;
    if (!command->redirections)
        return (1);
    i = 0;
    while (i < command->redirections->length)
    {
        redirection = (t_redirection *)ft_get_elem(command->redirections, i);
		if (redirection->type == e_redirection_input)
			made = make_input_redirection(redirection, shell);
		else if (redirection->type == e_redirection_output)
			made = make_output_redirection(redirection, shell);
		else if (redirection->type == e_redirection_append_out)
			made = make_output_redirection(redirection, shell);
		else if (redirection->type == e_redirection_heredoc)
			made = make_heredoc_red(redirection, shell);
		if (made == false)
			break;
        i++;
    }
	if (made == false)
		return (1);
	return (0);
}

void	destroy_redirections(t_array *redirections)
{
	t_redirection	*redirection;

	while (redirections->length)
	{
		redirection = (t_redirection *)ft_pop(redirections);
		free(redirection->filename);
		free(redirection);
	}
	free(redirections);
}
