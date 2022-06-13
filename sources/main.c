/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkasongo <jkasongo@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 18:43:09 by jkasongo          #+#    #+#             */
/*   Updated: 2022/06/10 17:42:35 by jkasongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_mshell	g_shell;

int	main(int argc, char *argv[], char *envp[])
{
	(void)argc;
	(void)argv;
	g_shell.env = 0;
	g_shell.paths = 0;
	ft_create_environ(envp);
	init_shell_jobs_capability();
	minishell_loop();
	return (g_shell.status);
}
