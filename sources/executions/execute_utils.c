/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkasongo <jkasongo@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 17:53:36 by jkasongo          #+#    #+#             */
/*   Updated: 2022/06/30 19:47:01 by jkasongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipelines.h"
#include <errno.h>
#include <string.h>

void	set_shell_error(t_shell *shell, char *msg, int code)
{
	if (shell->error_msg)
		free(shell->error_msg);
	shell->error_msg = msg;
	shell->status = code;
}

static void	*map_ret_content(void *content, int index)
{
	(void)index;
	return (content);
}

static void	*map_join_key_content(void *content, char *key, size_t index)
{
	char	*word;
	size_t	len_key;
	size_t	len_content;
	char	*data;

	data = (char *)content;
	len_key = ft_strlen(key);
	len_content = ft_strlen(data);
	word = (char *)ft_calloc(1, (len_key + len_content + 2));
	index = 0;
	while (index < len_key)
	{
		word[index] = key[index];
		index++;
	}
	word[index] = '=';
	index = 0;
	while (index < len_content)
	{
		word[(len_key + 1 + index)] = data[index];
		index++;
	}
	word[len_key + 1 + index] = 0;
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

	if (!command->arguments && command->cmd)
	{
		args = (char **)ft_calloc(1, (2 * sizeof(char *)));
		args[0] = ft_strdup(command->cmd);
		args[1] = NULL;
		return (args);
	}
	tmp_args = (char **)ft_map(command->arguments, map_ret_content);
	len = command->arguments->length;
	args = (char **)ft_calloc(1, ((len + 2) * sizeof(char *)));
	args[0] = ft_strdup(command->cmd);
	i = 0;
	while (i < len)
	{
		args[i + 1] = ft_strdup(tmp_args[i]);
		i++;
	}
	args[i + 1] = NULL;
	free(tmp_args);
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
	len = command->env->length;
	tmp_env = (char **)ft_map_d(command->env, map_join_key_content);
	env = (char **)ft_calloc((len + 1), sizeof(char *));
	while (i < len)
	{
		env[i] = (char *)tmp_env[i];
		i++;
	}
	env[i] = (char *) NULL;
	free(tmp_env);
	return (env);
}
