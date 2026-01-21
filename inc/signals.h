/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbindl <pbindl@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 17:49:28 by pbindl            #+#    #+#             */
/*   Updated: 2026/01/15 22:48:15 by pbindl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

# include <stdbool.h>

int		addsighandler(int sig, void (*handler)(int), int flags);
void	signals_init(void);
void	signals_forward_int(int sig);

#endif
