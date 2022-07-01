/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_cmd_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkasongo <jkasongo@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 21:53:36 by jkasongo          #+#    #+#             */
/*   Updated: 2022/06/30 19:51:32 by jkasongo         ###   ########.fr       */
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
