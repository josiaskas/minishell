/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkasongo <jkasongo@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 17:53:36 by jkasongo          #+#    #+#             */
/*   Updated: 2022/06/11 17:53:38 by jkasongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipelines.h"

void	print_cmd_error(char *cmd_name, char *error_msg)
{
	if (cmd_name)
	{
		ft_putstr_fd(cmd_name, STDERR_FILENO);
	}
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putendl_fd(error_msg, STDERR_FILENO);
}

void	*map_ret_content(void *content, int index)
{
	(void)index;
	return content;
}

void	*map_join_key_content(void *content, char *key, size_t index)
{
	char	*word;
	char	*temp;

	(void)index;
	temp = ft_strjoin(key, "=");
	word = ft_strjoin(temp, (char *)content);
	free(temp);
	return word;
}