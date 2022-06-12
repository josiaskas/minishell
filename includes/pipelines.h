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

int		execute_pipeline(t_shell *shell, char *line);

int		make_pipeline(t_shell *shell, t_command *cmd);
int		execute_cmd(t_shell *shell, t_command *cmd);
void	exit_subshell_cmd(t_shell *shell, t_command *curr_command);

void	set_len_of_piped_command(t_shell *shell);
void	set_shell_error(t_shell *parser, char *msg, int code);
void	close_all_pipes(int *pipes[], int len);


int		build_cmd_redirections(t_shell *shell, t_command *command);
void	destroy_redirections(t_array *redirections);

void	destroy_shell_data(t_shell *shell);

#endif //PIPELINES_H
