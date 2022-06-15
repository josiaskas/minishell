/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkasongo <jkasongo@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 21:12:33 by jkasongo          #+#    #+#             */
/*   Updated: 2022/06/15 11:53:11 by jkasongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/status.h"
#include <signal.h>
#include <readline/history.h>
#include <readline/readline.h>

static int	setup_signal(int signal, void (*handler)(int))
{
	struct sigaction	s;

	s.sa_handler = handler;
	sigemptyset(&s.sa_mask);
	s.sa_flags = SA_RESTART;
	return (sigaction(signal, &s, NULL));
}

void	handle_sigint(int signum)
{
	(void)signum;
	ft_putstr_fd("\n", STDOUT_FILENO);
	//	ft_putstr_fd(rl_prompt, STDOUT_FILENO);
	if (rl_line_buffer)
		free(rl_line_buffer);
	rl_line_buffer = ft_strdup("");
	rl_on_new_line();
}

void	activate_signal_handling(void)
{
	setup_signal(SIGINT, handle_sigint);
}

void	set_default_signal_handling(void)
{
	setup_signal(SIGINT, SIG_DFL);
}

void	ignore_signal_handling(void)
{
	setup_signal(SIGINT, SIG_IGN);
}
