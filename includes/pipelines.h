/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipelines.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkasongo <jkasongo@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 15:56:42 by jkasongo          #+#    #+#             */
/*   Updated: 2022/06/10 19:19:35 by jkasongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPELINES_H
# define PIPELINES_H
# include "parser.h"
# include "minishell.h"

int		execute_pipeline(t_shell *shell);

int		make_pipeline(t_shell *shell, t_command *cmd);
void	wait_all_child_process(t_shell *shell);
int		execute_cmd(t_shell *shell, t_command *cmd);
int		ft_execve(t_shell *shell, t_command *cmd);
void	exit_subshell_cmd(t_shell *shell, t_command *curr_command);
int		get_sub_shell_last_cmd_status(t_command *commands);

void	set_len_of_piped_command(t_shell *shell);
void	set_shell_error(t_shell *shell, char *msg, int code);
void	close_all_pipes(int *pipes[], int len);
int		build_cmd_redirections(t_shell *shell, t_command *command);
bool	m_heredoc_r(t_redirection *redirection, t_shell *shell, t_command *cmd);
void	print_heredoc_lex(char *sentence, int write_pipe);
void	destroy_redirections(t_array *redirections);
int		build_all_cmd_r(t_shell *shell, t_command *command, int *pipes[]);

void	destroy_shell_data(t_shell *shell);
void	print_cmd_error(char *cmd_name, char *error_msg);
char	**get_args_array(t_command *command);
char	**get_env_array(t_command *command);
#endif //PIPELINES_H
