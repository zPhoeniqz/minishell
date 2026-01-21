/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbindl <pbindl@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 17:44:36 by pbindl            #+#    #+#             */
/*   Updated: 2026/01/07 18:01:39 by pbindl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PATH_H
# define PATH_H

# include <stdbool.h>

typedef enum e_cwdaction
{
	READ,
	UPDATE,
	FREE
}			t_cwdaction;

char		*pathjoin(const char *s1, const char *s2);
const char	*cwd_state(t_cwdaction action);
bool		cwd_change(const char *path);

#endif
