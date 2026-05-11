/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_setenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbindl <pbindl@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/11 20:06:39 by pbindl            #+#    #+#             */
/*   Updated: 2026/05/11 20:15:42 by pbindl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include <stdbool.h>
#include <stdlib.h>

int	find_env(const char **envp, const char *name)
{
	size_t	lname;
	int		out;

	lname = ft_strlen(name);
	out = 0;
	while (envp[out])
	{
		if (ft_strncmp(name, envp[out], lname) == 0)
			return (out);
		out++;
	}
	return (-1);
}

static char	*make_envstr(const char *name, const char *value)
{
	char	*envstr;
	size_t	len;

	len = ft_strlen(name) + 2;
	if (value)
		len += ft_strlen(value);
	envstr = ft_calloc(len, 1);
	if (!envstr)
		return (NULL);
	ft_memcpy(envstr, name, ft_strlen(name));
	envstr[ft_strlen(name)] = '=';
	if (value)
		ft_memcpy(envstr + ft_strlen(name) + 1, value, ft_strlen(value));
	else
		envstr[ft_strlen(name)] = 0;
	return (envstr);
}

static int	envcpy(char ***envp, char *envstr)
{
	int		idx;
	char	**newenv;

	idx = 0;
	while ((*envp)[idx])
		idx++;
	newenv = ft_calloc(idx + 2, sizeof(char *));
	if (!newenv)
		return (free(envstr), 1);
	ft_memcpy(newenv, *envp, idx * sizeof(char *));
	newenv[idx] = envstr;
	free(*envp);
	*envp = newenv;
	return (0);
}

int	ft_setenv(char ***envp, const char *name, const char *value, bool rewrite)
{
	int		idx;
	char	*envstr;

	idx = find_env((const char **)(*envp), name);
	if (idx != -1 && !rewrite)
		return (0);
	envstr = make_envstr(name, value);
	if (!envstr)
		return (1);
	if (idx != -1)
	{
		free((*envp)[idx]);
		(*envp)[idx] = envstr;
		return (0);
	}
	return (envcpy(envp, envstr));
}
