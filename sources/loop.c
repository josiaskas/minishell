/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkasongo <jkasongo@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 22:56:51 by jkasongo          #+#    #+#             */
/*   Updated: 2022/06/22 18:21:23 by jkasongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/pipelines.h"
#include <unistd.h>
#include <stdio.h>
#include <readline/history.h>

static void	loop_banner(void)
{
	ft_putstr_fd(" __  __ ___ _   _ ___ ____  _   _ _____ _     _\n", 1);
	ft_putstr_fd("|  \\/  |_ _| \\ | |_ _/ ___|| | | | ____| |   | |\n", 1);
	ft_putstr_fd("| |\\/| || ||  \\| || |\\___ \\| |_| |  _| | |   | |\n", 1);
	ft_putstr_fd("| |  | || || |\\  || | ___) |  _  | |___| |___| |___\n", 1);
	ft_putstr_fd("|_|  |_|___|_| \\_|___|____/|_| |_|_____|_____|_____|\n", 1);
}

static char	*make_prompt_line(void)
{
	char	*line;
	char	*tmp;
	char	*prompt;

	line = NULL;
	prompt = make_prompt(true);
	rl_on_new_line();
	line = readline(prompt);
	if (prompt)
		free(prompt);
	if (!line)
		return (NULL);
	if (ft_strlen(line)){
		tmp = ft_strtrim(line, "\n\t\v\f\r ");
		free(line);
		line = tmp;
		if (ft_strlen(line))
			add_history(line);
	}
	return (line);
}

// return 0 or positive in case of an error (exit status)
static int	shell_loop_logic(char *line)
{
	int	code;

	code = 0;
	if (ft_strlen(line) > 0)
		code = execute_pipeline(parse_shell_line(line));
	return (code);
}

int	minishell_loop(void)
{
	char	*line;
	int		code;

	line = NULL;
	loop_banner();
	while (1)
	{
		activate_signal_handling();
		line = make_prompt_line();
		if (!line)
		{
			ft_putendl_fd("exit", STDOUT_FILENO);
			code = -1;
		}
		else
			code = shell_loop_logic(line);
		if (code == -1)
		{
			code = g_shell.status;
			break ;
		}
	}
	clear_history();
	return (code);
}
