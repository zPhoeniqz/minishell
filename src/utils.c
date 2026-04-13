/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whuth <whuth@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 16:51:36 by whuth             #+#    #+#             */
/*   Updated: 2026/03/19 18:09:39 by pbindl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include <stdlib.h>

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
