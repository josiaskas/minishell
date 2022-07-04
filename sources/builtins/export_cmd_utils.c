/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_cmd_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkasongo <jkasongo@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 21:53:36 by jkasongo          #+#    #+#             */
/*   Updated: 2022/07/04 16:42:08 by jkasongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtins.h"

char	*ft_get_env_varname(const char *env_line)
{
	char	*varname;
	size_t	len;
	size_t	i;

	i = 0;
	len = ft_strlen(env_line);
	if (len == 0)
		return (NULL);
	varname = NULL;
	while (i < len)
	{
		if (env_line[i] == '=')
			break ;
		i++;
	}
	varname = (char *)ft_calloc(1, i + 1);
	ft_strlcpy(varname, env_line, i + 1);
	return (varname);
}

static void	*map_join_key_c_with_eq(void *content, char *key, size_t index)
{
	char	*word;
	char	*part1;
	char	*part2;
	char	*data;

	data = (char *)content;
	(void)index;
	part1 = ft_strjoin(key, "=\"");
	part2 = ft_strjoin(data, "\"");
	word = ft_strjoin(part1, part2);
	free(part1);
	free(part2);
	return (word);
}

char	**get_env_array_with_eq(t_command *command)
{
	char	**env;
	char	**tmp_env;
	size_t	i;
	size_t	len;

	env = NULL;
	i = 0;
	len = command->env->length;
	tmp_env = (char **)ft_map_d(command->env, map_join_key_c_with_eq);
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
