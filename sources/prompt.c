/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkasongo <jkasongo@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 22:56:51 by jkasongo          #+#    #+#             */
/*   Updated: 2022/06/15 11:42:23 by jkasongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/parser.h"
#include "../includes/pipelines.h"
#include <unistd.h>
#include <readline/history.h>

static char	*make_prompt_line(void)
{
	char	*line;
	char	*prompt;

	line = NULL;
	prompt = make_prompt(true);
	rl_on_new_line();
	line = readline(prompt);
	free(prompt);
	if (!line)
		return (NULL);
	if (ft_strlen(line))
		add_history(line);
	return (line);
}

int	minishell_loop(void)
{
	char	*line;
	int		code;

	activate_signal_handling();
	line = NULL;
	while (1)
	{
		if (line)
			free(line);
		line = NULL;
		line = make_prompt_line();
		if (ft_strlen(line) > 0)
		{
			code = execute_pipeline(parse_shell_line(line));
			if (code == -1)
			{
				free(line);
				code = g_shell.status;
				break ;
			}
		}
	}
	delete_environ();
	return (code);
}
