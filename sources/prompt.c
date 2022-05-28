/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkasongo <jkasongo@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 22:56:51 by jkasongo          #+#    #+#             */
/*   Updated: 2022/05/02 12:24:28 by jkasongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "minishell.h"

static char	*make_prompt_line(int code)
{
	char	*line;
	char	*prompt;

	line = NULL;
	prompt = make_prompt(code, true);
	line = readline(prompt);
	free(prompt);
	if (!line)
		return (NULL);
	if (ft_strlen(line) > 0)
		add_history(line);
	return(line);
}

void	*print_env_var(void *c, char *key, size_t i)
{
	char	*value;

	value = (char *)c;
	printf("%lu | \033[0;32m%s\033[0;39m = %s \n", i, key, value);
	return 0;
}

int		minishell_loop(char *envp[])
{
	char		*line;
	int			code;

	code = 0;
	line = NULL;
	ft_create_environ(envp);
	while (1)
	{
		line = make_prompt_line(code);
		if (ft_strncmp(line, "exit", 5) == 0)
			break ;
		code = parse_line(line);
		free(line);
	}
	free(line);
	delete_environ();
	return (0);
}
