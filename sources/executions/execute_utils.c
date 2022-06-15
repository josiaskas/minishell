/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkasongo <jkasongo@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 17:53:36 by jkasongo          #+#    #+#             */
/*   Updated: 2022/06/15 11:43:18 by jkasongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipelines.h"
#include <errno.h>
#include <string.h>

void	set_shell_error(t_shell *parser, char *msg, int code)
{
	if (parser->error_msg)
		free(parser->error_msg);
	parser->error_msg = msg;
	parser->status = code;
}

static void	*map_ret_content(void *content, int index)
{
	(void)index;
	return (content);
}

static void	*map_join_key_content(void *content, char *key, size_t index)
{
	char	*word;
	char	*temp;

	(void)index;
	temp = ft_strjoin(key, "=");
	word = ft_strjoin(temp, (char *)content);
	free(temp);
	return (word);
}

/*
 * create a new (char **) from cmd->arguments and add cmd->name to it
 * Add null at the end
 * size of returned array is cmd->arguments->length + 1
 * Need to all be free after usage
 */
char	**get_args_array(t_command *command)
{
	char	**args;
	char	**tmp_args;
	size_t	i;
	size_t	len;

	args = NULL;
	i = 0;
	if (!command->arguments && command->cmd)
	{
		args = (char **)ft_calloc(1, (2 * sizeof(char *)));
		args[0] = ft_strdup(command->cmd);
		args[1] = NULL;
		return (args);
	}
	tmp_args = (char **)ft_map(command->arguments, map_ret_content);
	len = command->arguments->length;
	args = (char **)ft_calloc(1, ((len + 1) * sizeof(char *)));
	while (i < len)
	{
		args[i] = ft_strdup(tmp_args[i]);
		i++;
	}
	args[i] = NULL;
	return (args);
}

/*
 * create a new (char **) from cmd->env
 * Add NULL at the end
 * Size is cmd->env->length + 1
 * Need to all be free after usage
 */
char	**get_env_array(t_command *command)
{
	char	**env;
	char	**tmp_env;
	size_t	i;
	size_t	len;

	env = NULL;
	i = 0;
	tmp_env = (char **)ft_map_d(command->env, map_join_key_content);
	len = command->env->length;
	env = (char **)ft_calloc(1, ((len + 1) * sizeof(char *)));
	while (i < len)
	{
		env[i] = ft_strdup(tmp_env[i]);
		i++;
	}
	env[i] = NULL;
	return (env);
}
