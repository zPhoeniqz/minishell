/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbindl <pbindl@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 18:27:41 by pbindl            #+#    #+#             */
/*   Updated: 2026/05/11 20:57:08 by pbindl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/signals.h"
#include "../libft/libft.h"
#include <readline/readline.h>
#include <signal.h>
#include <stdio.h>
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

void	sigfunc_redisplay_prompt(int sig)
{
	(void)sig;
	rl_replace_line("", 0);
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_redisplay();
	g_exit_code = 130;
}

void	sigfunc_return_to_prompt(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	g_exit_code = 130;
}
