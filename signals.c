/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbindl <pbindl@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 18:27:41 by pbindl            #+#    #+#             */
/*   Updated: 2026/01/15 22:49:59 by pbindl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/signals.h"
#include "libft/libft.h"
#include "signal.h"
#include <bits/types/siginfo_t.h>
#include <readline/readline.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int	addsighandler(int sig, void (*handler)(int), int flags)
{
	struct sigaction	s;
	int					out;

	out = 0;
	ft_bzero(&s, sizeof(s));
	s.sa_handler = handler;
	sigemptyset(&s.sa_mask);
	out += sigemptyset(&s.sa_mask);
	s.sa_flags = flags;
	out += sigaction(sig, &s, NULL);
	return (out);
}

void	signals_forward_int(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_redisplay();
}

void	signals_init(void)
{
	addsighandler(SIGQUIT, SIG_IGN, 0);
	addsighandler(SIGINT, signals_forward_int, SA_RESTART);
}
