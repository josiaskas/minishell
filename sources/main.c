/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkasongo <jkasongo@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 18:43:09 by jkasongo          #+#    #+#             */
/*   Updated: 2022/03/12 14:13:52 by jkasongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	char	*line;

	line = NULL;
	ft_putstr_fd("\033[0;33m", STDOUT_FILENO);
	ft_putstr_fd("Minishell >", STDOUT_FILENO);
	ft_putstr_fd("\033[0;39m ", STDOUT_FILENO);
	while (get_next_line(STDIN_FILENO, &line) > 0)
	{
		parse_args(line);
		free(line);
		ft_putstr_fd("\033[0;33m", STDOUT_FILENO);
		ft_putstr_fd("Minishell >", STDOUT_FILENO);
		ft_putstr_fd("\033[0;39m ", STDOUT_FILENO);
	}
	return (0);
}
