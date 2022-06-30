/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_cmd_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkasongo <jkasongo@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 21:53:36 by jkasongo          #+#    #+#             */
/*   Updated: 2022/06/30 16:40:22 by jkasongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtins.h"

char	*ft_get_env_varname(char *env_line)
{
	char	*varname;
	size_t	len;
	size_t	i;

	i = 0;
	len = ft_strlen(env_line);
	if (len == 0)
		return (NULL);
	varname = (char *)ft_calloc(1, len + 1);
	while (i < len)
	{
		if (env_line[i] == '=')
			break;
		varname[i] = env_line[i];
		i++;
	}
	return (varname);
}

char	*ft_get_env_value_in_line(char *env_line)
{
	char	*value;
	char	*word;
	size_t	i;

	i = 0;
	value = NULL;
	word = ft_strchr(env_line, '=');
	if (word)
	{
		value = (char *)ft_calloc(1, ft_strlen(word) + 1);
		while (word[i + 1] != 0)
		{
			value[i] = word[i + 1];
			i++;
		}
		value[i] = 0;
	}
	return (value);
}