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

int	main(int argc, char *argv[], char *envp[])
{
	(void)argc;
	(void)argv;
	g_shell.env = 0;
	g_shell.paths = 0;
	ft_create_environ(envp);
	minishell_loop();
	return (g_shell.status);
}
