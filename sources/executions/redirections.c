/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkasongo <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 16:16:43 by jkasongo          #+#    #+#             */
/*   Updated: 2022/06/07 16:17:02 by jkasongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipelines.h"
#include <fcntl.h>
#include <errno.h>

bool    heredoc(char *delimiter)
{

}

bool    make_redirection_on_cmd(t_redirection *redirection, t_command *cmd)
{
    int     fd;

    if (!redirection || !cmd)
        return (false);
    if (redirection->type == e_redirection_input)
        fd = open(redirection->filename, O_RDONLY);
    else if (redirection->type == e_redirection_heredoc)
        fd = open(redirection->filename, O_CREAT | O_RDWR | O_TRUNC, 0644);
    else if (redirection->type == e_redirection_output)
        fd = open(redirection->filename, O_CREAT | O_RDWR | O_TRUNC, 0644);
    else if (redirection->type == e_redirection_append_out)
        fd = open(redirection->filename, O_CREAT | O_RDWR | O_APPEND, 0644);
    return (true);
}

int    build_cmd_redirections(t_command *command)
{
    int             status;
    size_t          i;
    t_redirection   *redirection;

    status = 0;
    if (!command->redirections)
        return (1);
    i = 0;
    while (i < command->redirections->length)
    {
        redirection = ft_get_elem(command->redirections, i);
        i++;
    }
    return (status);
}

