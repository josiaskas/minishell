/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkasongo <jkasongo@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 21:28:14 by jkasongo          #+#    #+#             */
/*   Updated: 2022/06/10 19:20:14 by jkasongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STATUS_H
# define STATUS_H

# include "minishell.h"
# include "parser.h"

char	*make_prompt(bool with_bar);
void	ft_create_environ(const char *envp[]);
void	delete_environ(void);
void	handle_sigint(int signum);
int		setup_signal(int signal, void (*handler)(int));
void	activate_signal_handling(void);
void	ignore_signal_handling(void);
void	set_default_signal_handling(void);
void	rl_replace_line(const char *text, int clear_undo);
void	set_env_pwd(t_shell *shell);
void	make_bin_search_paths(char *path_var);
#endif
