/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whuth <whuth@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 16:51:36 by whuth             #+#    #+#             */
/*   Updated: 2026/05/11 17:14:36 by whuth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

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
	memcpy(envstr, name, ft_strlen(name));
	envstr[ft_strlen(name)] = '=';
	if (value)
		memcpy(envstr + ft_strlen(name) + 1, value, ft_strlen(value));
	else
		envstr[ft_strlen(name)] = 0;
	return (envstr);
}

static int	envp_append(char ***envp, char *envstr)
{
	char	**newenv;
	int		idx;

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
	return (envp_append(envp, envstr));
}

char	*ft_getenv(char **envp, const char *name)
{
	size_t	len;
	char	*eqs;

	len = ft_strlen(name);
	while (*envp)
	{
		if (ft_strncmp(*envp, name, len) == 0)
		{
			eqs = ft_strchr(*envp, '=');
			if (!eqs)
				return (NULL);
			return (eqs + 1);
		}
		envp++;
	}
	return (NULL);
}

bool	ft_isspace(char c)
{
	return (c == ' ' || c == '\f' || c == '\n' || c == '\r' || c == '\t'
		|| c == '\v');
}
