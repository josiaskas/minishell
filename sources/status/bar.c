/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bar.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkasongo <jkasongo@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 21:12:33 by jkasongo          #+#    #+#             */
/*   Updated: 2022/06/15 11:41:47 by jkasongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/status.h"

static char	*get_home_pwd(char *path)
{
	t_dic_node	*home_pwd;
	char		*home;

	home_pwd = ft_elem_dic(g_shell.env, "HOME");
	if (home_pwd)
	{
		home = (char *)home_pwd->content;
		if (ft_strnstr(path, home, ft_strlen(path)))
			return (ft_strjoin("~", (path + ft_strlen(home))));
	}
	return (ft_strdup(path));
}

static char	*make_status_bar(char *path, char *git_branch)
{
	char	*temp;
	char	*bar;

	bar = NULL;
	bar = ft_strjoin("\033[36m", path);
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
	free(path);
	free(git_branch);
	return (temp);
}

char	*make_prompt(bool with_bar)
{
	char	*prompt;
	char	*bar;
	char	*path;

	path = g_shell.pwd;
	bar = NULL;
	if (with_bar)
		bar = make_status_bar(get_home_pwd(path), NULL);
	if (g_shell.status == 0)
		prompt = ft_strjoin(bar, "\033[32m$>\033[0;39m ");
	else
		prompt = ft_strjoin(bar, "\033[31m$>\033[0;39m ");
	free(bar);
	return (prompt);
}
