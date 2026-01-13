/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbindl <pbindl@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 17:42:40 by pbindl            #+#    #+#             */
/*   Updated: 2026/01/13 19:29:12 by pbindl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/path.h"
#include "libft/libft.h"
#include <readline/readline.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>

const char	*cwd_state(t_cwdaction action)
{
	static char	*cwd = NULL;

	if (action == UPDATE || (action == READ && !cwd))
	{
		free(cwd);
		cwd = getcwd(NULL, 0);
	}
	if (action == FREE)
	{
		free(cwd);
		cwd = NULL;
	}
	return (cwd);
}

bool	cwd_change(const char *path)
{
	if (chdir(path) == -1)
		return (false);
	cwd_state(UPDATE);
	return (true);
}

char	*pathjoin(const char *s1, const char *s2)
{
	size_t	l1;
	bool	separator_exists;
	size_t	len;
	char	*out;

	l1 = ft_strlen(s1);
	if (l1 <= 1)
		return (NULL);
	separator_exists = s1[l1 - 1] == '/' || s2[0] == '/';
	len = l1 + !separator_exists + ft_strlen(s2) + 1;
	out = malloc(len);
	if (!out)
		return (NULL);
	ft_strlcpy(out, s1, len);
	if (!separator_exists)
		out[l1] = '/';
	ft_strlcat(out, s2, len);
	return (out);
}
