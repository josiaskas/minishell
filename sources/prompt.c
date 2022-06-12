/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkasongo <jkasongo@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 22:56:51 by jkasongo          #+#    #+#             */
/*   Updated: 2022/06/10 19:25:22 by jkasongo         ###   ########.fr       */
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
	char	*tmp;

	line = NULL;
	prompt = make_prompt(true);
	line = readline(prompt);
	free(prompt);
	if (!line)
		return (NULL);
	tmp = ft_strtrim(line, "\t\r\n\v\f ");
	free(line);
	line = tmp;
	if (ft_strlen(line))
		add_history(line);
	return (line);
}

// void	*print_env_var(void *c, char *key, size_t i)
//{
//	char	*value;
//
//	value = (char *)c;
//	printf("%lu | \033[0;32m%s\033[0;39m = %s \n", i, key, value);
//	return 0;
// }

int	minishell_loop(void)
{
	char	*line;
	int		code;

	line = NULL;
	g_shell.status = 0;
	g_shell.error_msg = NULL;
	code = 0;
	while (1)
	{
		line = make_prompt_line();
		if (ft_strlen(line) > 0)
		{
			code = execute_pipeline(parse_shell_line(line), line);
			if (code == -1)
			{
				code = g_shell.status;
				break;
			}
		}
	}
	delete_environ();
	return (code);
}
