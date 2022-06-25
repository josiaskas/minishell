/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkasongo <jkasongo@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 21:12:33 by jkasongo          #+#    #+#             */
/*   Updated: 2022/06/22 18:20:41 by jkasongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/status.h"
#include <signal.h>
#include <readline/readline.h>

int	setup_signal(int signal, void (*handler)(int))
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
	g_shell.status = 1;

	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	rl_cleanup_after_signal();
}

void	activate_signal_handling(void)
{
	setup_signal(SIGINT, handle_sigint);
	setup_signal(SIGQUIT, SIG_IGN);
}

void	set_default_signal_handling(void)
{
	setup_signal(SIGINT, SIG_DFL);
	setup_signal(SIGQUIT, SIG_DFL);
}

void	ignore_signal_handling(void)
{
	setup_signal(SIGINT, SIG_IGN);
	setup_signal(SIGQUIT, SIG_IGN);
}
