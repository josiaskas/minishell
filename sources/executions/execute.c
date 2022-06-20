/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkasongo <jkasongo@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 17:53:36 by jkasongo          #+#    #+#             */
/*   Updated: 2022/06/20 17:45:11 by jkasongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipelines.h"
#include "../../includes/builtins.h"

/*
 * Print parser error and set the status code to 258
 */
static int	treat_parser_error(t_shell *shell)
{
	if (shell->error_msg)
		print_cmd_error("minishell", shell->error_msg);
	else
		print_cmd_error("minishell", "syntax error");
	g_shell.status = 258;
	destroy_shell_data(shell);
	return (0);
}

static int	execute_internal(t_shell *shell, t_command *cmd)
{
	if (cmd->internal_cmd == e_cmd_intern_exit)
		return (exit_builtin_cmd(shell, cmd));
	else if (cmd->internal_cmd == e_cmd_intern_cd)
		return (cd_builtin_cmd(shell, cmd));
	else if (cmd->internal_cmd == e_cmd_intern_echo)
		return (echo_builtin_cmd(shell, cmd));
	else if (cmd->internal_cmd == e_cmd_intern_pwd)
		return (pwd_builtin_cmd(shell, cmd));
	else if (cmd->internal_cmd == e_cmd_intern_env)
		return (env_builtin_cmd(shell, cmd));
	shell->status = 0;
	return (0);
}

/*
 * Execute sub_shell_cmd called by each made cmd inside the pipeline
 * Return 1 if failed normally except for builtins no return is made
 */
int	execute_cmd(t_shell *shell, t_command *cmd)
{
	set_default_signal_handling();
	if (cmd->is_internal)
		return (execute_internal(shell, cmd));
	return (ft_execve(shell, cmd));
}

// execute internal directly inside parent if unique in pipeline
static int	execute_spec_internal_cmd(t_shell *shell, t_command *cmd)
{
	int	status;

	status = 0;
	shell->is_parent = true;
	cmd->fd[1] = STDOUT_FILENO;
	if (cmd->redirections)
		status = build_all_cmd_r(shell, cmd, NULL);
	if (status > 0)
	{
		g_shell.status = 1;
		return (status);
	}
	if (cmd->internal_cmd == e_cmd_intern_exit)
	{
		exit_builtin_cmd(shell, cmd);
		return (-1);
	}
	status = execute_internal(shell, cmd);
	return (status);
}

/*
 * Execute the pipeline
 * Return 0 in case of parser syntax error but set g_shell.status
 * Return 1 if exit command was called
 */
int	execute_pipeline(t_shell *shell)
{
	int	code;

	if (shell->syntax_error)
		return (treat_parser_error(shell));
	set_len_of_piped_command(shell);
	if ((shell->pipes_len == 1) && (shell->commands_list->is_internal))
		code = execute_spec_internal_cmd(shell, shell->commands_list);
	else
		code = make_pipeline(shell, shell->commands_list);
	if (code > 0 && shell->error_msg)
		print_cmd_error("minishell", shell->error_msg);
	destroy_shell_data(shell);
	return (code);
}
