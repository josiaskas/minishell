/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkasongo <jkasongo@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 22:56:51 by jkasongo          #+#    #+#             */
/*   Updated: 2022/03/13 23:55:33 by jkasongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "minishell.h"

// read file iniside .git to know the current branch on head
static char	*get_git_branch(char *path)
{
	char	*branch_name;

	if (!path)
		return (NULL);
	branch_name = "master";
	return branch_name;
}

static char	*get_prompt_line(int code, char *path)
{
	char	*line;
	char	*prompt;
	char	*tmp;

	line = NULL;
	prompt = make_prompt(code, true, path, get_git_branch(path));
	line = readline(prompt);
	free(prompt);
	if (!line)
		return (NULL);
	tmp = ft_strtrim(line, "\t\r\n\v\f ");
	free(line);
	line = tmp;
	if (ft_strlen(line))
		add_history(line);
	return(line);
}

int		minishell_loop(void)
{
	char	*line;
	int		code;

	code = 0;
	line = NULL;
	while (1)
	{
		line = get_prompt_line(0, "PATH");
		code = parse_line(line);
		free(line);
	}

}
