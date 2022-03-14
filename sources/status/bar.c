/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bar.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkasongo <jkasongo@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 21:12:33 by jkasongo          #+#    #+#             */
/*   Updated: 2022/03/14 00:00:12 by jkasongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "status.h"

static char	*make_shell_status_bar(const char *path, char *git_branch)
{
	char	*temp;
	char	*git_color;
	char	*bar;

	temp = NULL;
	bar = NULL;
	git_color = "\033[37m |  on \033[32m";
	bar = ft_strjoin("\n\033[100;36m ", path);
	if (ft_strlen(git_branch) > 0)
	{
		temp = ft_strjoin(bar, "\033[37m |  on\033[32m ");
		free(bar);
		bar = temp;
		temp = ft_strjoin(bar, git_branch);
		free(bar);
		bar = temp;
	}
	temp = ft_strjoin(bar, "\033[0;39m");
	free(bar);
	bar = temp;
	return (temp);
}

char	*make_prompt(int code, bool with_bar, char *path, char *git)
{
	char	*prompt;
	char	*bar;

	prompt = NULL;
	bar = NULL;
	if (with_bar)
		bar = make_shell_status_bar(path, git);
	if (code >= 0)
		prompt = ft_strjoin(bar, "\033[32m\n>\033[0;39m");
	else
		prompt = ft_strjoin(bar, "\033[31m\n>\033[0;39m");
	free(bar);
	return (prompt);
}
