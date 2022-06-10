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

static int **build_pipes(t_shell_parser *parser, t_command *command)
{
    int         **pipes;
    int         i;
    int         len;

    i = 0;
    len = 0;
    while (command)
    {
        command = command->pipe;
        len++;
    }
    pipes = (int **)ft_calloc(len, sizeof(int *));
    while ((i < len) && (pipes))
    {
        pipes[i] = (int *)ft_calloc(2, sizeof(int));
        if (pipe(pipes[i]) == -1)
        {
            set_shell_error(parser, strerror(errno), 1);
            break;
        }
        i++;
    }
    parser->pipes_len = len;
    return (pipes);
}

static int  assign_pipes(int *pipes_made[], t_command *cmd, int pipes_len)
{
    int data_pipes[2];
    int i;

    i = 0;
    if (!cmd || !pipes_made)
        return (1);
    while (i < pipes_len)
    {
        data_pipes[0] = pipes_made[i][0];
        data_pipes[1] = pipes_made[i][1];
        if (i == 0)
            data_pipes[0] =  STDIN_FILENO;
        if ((i + 1) < (pipes_len))
            data_pipes[1] = pipes_made[i+1][1];
        if (i == (pipes_len - 1))
            data_pipes[1] = STDOUT_FILENO;
        cmd->fd[0] = data_pipes[0];
        cmd->fd[1] = data_pipes[1];
        cmd = cmd->pipe;
        i++;
    }
    return (0);
}

static void close_pipes(int *pipes[], int len)
{
    int i;

    i = 0;
    while(i < len)
    {
        close(pipes[i][0]);
        close(pipes[i][1]);
        i++;
    }
}

static int  exec_subshell(t_shell_parser *parser, t_command *command, int *pipes[])
{
    char *line;
    if (command->fd[0] != 0)
        dup2(command->fd[0], STDIN_FILENO);
    if (command->fd[1] != 1)
        dup2(command->fd[1], STDOUT_FILENO);
    close_pipes(pipes, parser->pipes_len);
    command->state = e_cmd_running;
    parser->status = 0;
    free(parser->error_msg);
    parser->error_msg = NULL;

    if (ft_strncmp(command->cmd, "read", 5) == 0 ){
        line = NULL;
        ft_printf("\n Reading first last pipes docs --\n", command->cmd);
        while (get_next_line(STDIN_FILENO,&line) > 0){
            ft_putstr_fd(line, STDOUT_FILENO);
            free(line);
        }
    }
    ft_printf("\n--- Here Data written in subshell by command: %s --\n", command->cmd);
    ft_print_cmd(command);
    ft_putendl_fd("end", STDOUT_FILENO);
    return (1);
}

int make_process(t_shell_parser *parser, t_command *command, int *pipes[])
{
    pid_t       pid;
    int         child_status;

    pid = fork();
    if (pid == -1)
    {
        set_shell_error(parser, strerror(errno), 1);
        return (1);
    }
    if (pid == 0)
        return (exec_subshell(parser, command, pipes));
    command->id = pid;
    command->state = e_cmd_waiting;
    if (command->fd[0] != 0)
        close(command->fd[0]);
    if (command->fd[1] != 1)
        close(command->fd[1]);
    waitpid(pid, &child_status, 0);
    command->status = child_status;
    return (0);
}

int make_pipeline(t_shell_parser *parser)
{
    int         **pipes;
    int         i;
    t_command   *cmd;

    cmd = parser->commands_list;
    pipes = build_pipes(parser, cmd);
    if (parser->status != 0)
        return (parser->status);
    i = assign_pipes(pipes, cmd, parser->pipes_len);
    if (i != 0)
        return (1);
    while (i < parser->pipes_len)
    {
       if (make_process(parser, cmd, pipes) > 0)
           return (1);
       cmd = cmd->pipe;
       i++;
    }
    free_array((void **)pipes, parser->pipes_len);
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
    code = make_pipeline(parser);
    if (parser->error_msg && (code != 0))
        ft_putstr_fd(parser->error_msg, STDERR_FILENO);
    destroy_parser(parser);
    return (code);
}
