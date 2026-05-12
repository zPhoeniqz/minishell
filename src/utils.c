/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whuth <whuth@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 16:51:36 by whuth             #+#    #+#             */
/*   Updated: 2026/05/12 16:03:26 by pbindl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
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

static char	*inc_shlvl(char *shlvl)
{
	char	*cur_shlvl_str;
	int		cur_shlvl;
	char	*out;

	cur_shlvl_str = ft_strchr(shlvl, '=') + 1;
	cur_shlvl = ft_atoi(cur_shlvl_str);
	if (cur_shlvl < 0)
		cur_shlvl = 0;
	cur_shlvl++;
	cur_shlvl_str = ft_itoa(cur_shlvl);
	if (!cur_shlvl_str)
		return (shlvl);
	out = ft_strjoin("SHLVL=", cur_shlvl_str);
	free(cur_shlvl_str);
	if (!out)
		return (shlvl);
	return (out);
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
	n = -1;
	while (envp[++n])
	{
		if (ft_strncmp(envp[n], "SHLVL", 5) == 0)
		{
			out[n] = inc_shlvl(envp[n]);
			continue ;
		}
		out[n] = ft_strdup(envp[n]);
		if (!out[n])
			return (arr_destroy((void **)out), NULL);
	}
	return (out);
}
