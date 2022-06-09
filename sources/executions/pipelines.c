/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipelines.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkasongo <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 14:52:09 by jkasongo          #+#    #+#             */
/*   Updated: 2022/06/07 14:52:14 by jkasongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipelines.h"
#include <errno.h>
#include <string.h>

int    set_shell_error(t_shell_parser *parser, char *msg, int code)
{
    free(parser->error_msg);
    parser->error_msg = ft_strdup(msg);
    return (code);
}

//static int execute_cmd(t_command *cmd, bool is_in_sub)
//{
//    cmd->state = e_cmd_waiting;
//    cmd->fd[0] = STDIN_FILENO;
//    cmd->fd[1] = STDOUT_FILENO;
//    cmd->fd[2] = STDERR_FILENO;
//
//    ft_print_cmd(cmd);
//    if (ft_strncmp(cmd->cmd, "exit", 5) == 0)
//        return (-128);
//    if (cmd->is_internal && is_in_sub)
//        return(-128);
//    else if (is_in_sub)
//    {
//        cmd->error_msg = ft_strdup("Pas de commande exec");
//        return(1);
//    }
//    return (0);
//}

int make_child_process(t_shell_parser *parser)
{
    t_command   *cmd;
    pid_t       pid;

    cmd = parser->commands_list;
    while(cmd)
    {
        pid = fork();
        if (pid == -1)
            return (set_shell_error(parser, strerror(errno), 1));
        cmd->id = pid;
        if (pid == 0)
        {
            parser->error_msg = ft_strdup("not exec");
            return (1);
        }
        else
        {
            waitpid(pid, NULL, 0);
            cmd = cmd->pipe;
        }
    }
    return (0);
}

void    destroy_parser(t_shell_parser *parser)
{
    t_command   *cmd;
    t_command   *tmp;

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
int run_pipeline(t_shell_parser *parser)
{
    int code;

    if (parser->syntax_error)
    {
        ft_putstr_fd(parser->error_msg, STDERR_FILENO);
        g_shell.status = 258;
        destroy_parser(parser);
        return (258);
    }
    code = make_child_process(parser);
    g_shell.status = code;
    if (parser->error_msg && (code > 0))
        ft_putstr_fd(parser->error_msg, STDERR_FILENO);
    destroy_parser(parser);
    return (code);
}
