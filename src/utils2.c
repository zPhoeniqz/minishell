/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whuth <whuth@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/11 17:11:33 by whuth             #+#    #+#             */
/*   Updated: 2026/05/11 17:12:24 by whuth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/utils.h"
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

void	*ft_realloc(void *ptr, size_t newsize)
{
	void	*out;

	if (!ptr)
		return (malloc(newsize));
	if (ptr && newsize == 0)
		return (ptr);
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

char	**dup_env(char **envp)
{
	size_t	n;
	char	**out;

	n = 0;
	while (envp[n])
		n++;
	out = ft_calloc(n + 1, sizeof(char *));
	if (!out)
		return (NULL);
	n = 0;
	while (envp[n])
	{
		out[n] = ft_strdup(envp[n]);
		if (!out[n])
			return (arr_destroy((void **)out), NULL);
		n++;
	}
	return (out);
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
