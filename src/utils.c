/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whuth <whuth@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 16:51:36 by whuth             #+#    #+#             */
/*   Updated: 2026/04/15 15:11:41 by pbindl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include <stdlib.h>
#include <string.h>

char	*ft_strcdup(const char *s, char c)
{
	int		i;
	char	*copy;

	i = 0;
	while (s[i] != c && s[i])
		++i;
	if (!(copy = malloc(sizeof(char) * i + 1)))
		return (NULL);
	i = 0;
	while (s[i] != c)
	{
		copy[i] = s[i];
		++i;
	}
	copy[i] = 0;
	return (copy);
}

void	*ft_realloc(void *ptr, size_t newsize)
{
	void	*out;

	if (!ptr)
		return (malloc(newsize));
	if (ptr && newsize == 0)
		return (free(ptr), ptr);
	out = malloc(newsize);
	if (!out)
		return (NULL);
	ft_memmove(out, ptr, newsize);
	return (out);
}

void	arr_destroy(void **arr)
{
	char	**oarr;

	if (!arr)
		return ;
	oarr = (char **)arr;
	while (*arr)
		free(*arr++);
	free(oarr);
}

void	ft_env_destroy(char **envp)
{
	if (!envp)
		return ;
	while (*envp)
		free(*envp++);
}

void	ft_env_make_individual_alloc(char **envp)
{
	while (*envp)
	{
		*envp = ft_strdup(*envp);
		if (!*envp)
			return (ft_env_destroy(envp));
		envp++;
	}
}

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

	envstr = ft_calloc(ft_strlen(name) + ft_strlen(value) + 2, 1);
	if (!envstr)
		return (NULL);
	memcpy(envstr, name, ft_strlen(name));
	envstr[ft_strlen(name)] = '=';
	memcpy(envstr + ft_strlen(name) + 1, value, ft_strlen(value));
	return (envstr);
}

int	ft_setenv(char **envp, const char *name, const char *value, bool rewrite)
{
	char	*valuestart;
	int		idx;
	char	*envstr;
	char	**newenv;

	idx = find_env((const char **)envp, name);
	if (idx != -1 && !rewrite)
		return (0);
	if (idx != -1)
	{
		valuestart = envp[idx] + ft_strlen(name) + 1;
		if (ft_strlen(valuestart) >= ft_strlen(value))
			return (ft_memmove(valuestart, value, ft_strlen(value)), 0);
		envstr = make_envstr(name, value);
		if (!envstr)
			return (1);
		free(envp[idx]);
		envp[idx] = envstr;
		return (0);
	}
	idx = 0;
	while (envp[idx])
		idx++;
	newenv = ft_calloc((idx + 2), sizeof(char *));
	if (!newenv)
		return (1);
	memcpy(newenv, envp, idx * sizeof(char *));
	newenv[idx] = make_envstr(name, value);
	arr_destroy((void **)envp);
	envp = newenv;
	return (newenv[idx] == NULL);
}
