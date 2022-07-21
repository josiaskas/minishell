/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkasongo <jkasongo@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 18:42:56 by jkasongo          #+#    #+#             */
/*   Updated: 2022/04/09 18:54:09 by jkasongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include "status.h"

typedef struct s_mshell
{
	t_array			*env;
	t_array			*paths;
	int				status;
	char			*pwd;
	char			*error_msg;
}	t_mshell;

extern t_mshell	g_shell;

void	command_mode_script(char *file_path);
void	get_flag_command_and_exec(char *flags, char *line);
int		minishell_loop(void);
bool	check_flags(char *flags, char flag);
#endif
