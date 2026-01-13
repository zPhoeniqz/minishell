/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbindl <pbindl@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 18:27:41 by pbindl            #+#    #+#             */
/*   Updated: 2026/01/13 19:59:56 by pbindl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include <signal.h>

int	addsighandler(int sig, void (*handler)(int))
{
	struct sigaction	s;
	int					out;

	out = 0;
	ft_bzero(&s, sizeof(s));
	s.sa_handler = handler;
	sigemptyset(&s.sa_mask);
	out += sigemptyset(&s.sa_mask);
	s.sa_flags = 0;
	out += sigaction(sig, &s, NULL);
	return (out);
}
