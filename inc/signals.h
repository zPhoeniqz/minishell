/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbindl <pbindl@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 17:49:28 by pbindl            #+#    #+#             */
/*   Updated: 2026/05/12 15:06:51 by pbindl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

# include <signal.h>
# include <stdbool.h>

extern volatile int	g_exit_code;

int					addsighandler(int sig, void (*handler)(int), int flags);
void				signals_init(void);
void				sigfunc_redisplay_prompt(int sig);
void				sigfunc_return_to_prompt(int sig);

#endif
