/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkasongo <jkasongo@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 18:43:09 by jkasongo          #+#    #+#             */
/*   Updated: 2022/06/22 18:21:09 by jkasongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_mshell	g_shell;

int	main(int argc, char *argv[], char const *envp[])
{
	//ft_bzero(&g_shell, sizeof(t_mshell));
	ft_create_environ(envp);
	if (argc >= 2)
	{
		if (argv[1][0] == '-' && argv[2])
			get_flag_command_and_exec(argv[1], argv[2]);
		else
			command_mode_script(argv[1]);
	}
	else
		minishell_loop();
	delete_environ();
	return (g_shell.status);
}
