/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_export.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbindl <pbindl@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/10 21:45:08 by pbindl            #+#    #+#             */
/*   Updated: 2026/05/10 22:26:44 by pbindl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/builtins.h"
#include "../inc/utils.h"
#include "../libft/libft.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static char	**var_split(char *s)
{
	size_t	namelen;
	char	**out;
	char	*eqs;

	out = ft_calloc(3, sizeof(char *));
	if (!out)
		return (NULL);
	eqs = ft_strchr(s, '=');
	if (eqs)
		namelen = eqs - s;
	else
		namelen = ft_strlen(s);
	out[0] = ft_calloc(namelen + 1, 1);
	if (!out[0])
		return (free(out), NULL);
	ft_memcpy(out[0], s, namelen);
	if (eqs && eqs[1])
		out[1] = ft_strdup(eqs + 1);
	else if (eqs && !eqs[1])
		out[1] = ft_strdup("");
	else
		out[1] = NULL;
	if (eqs && !out[1])
		return (arr_destroy((void **)out), NULL);
	return (out);
}

static void	print_entry(char *s)
{
	int	j;

	ft_putstr_fd("declare -x ", STDOUT_FILENO);
	j = 0;
	while (s[j] && s[j] != '=')
		ft_putchar_fd(s[j++], STDOUT_FILENO);
	if (!s[j])
	{
		ft_putchar_fd('\n', STDOUT_FILENO);
		return ;
	}
	ft_putchar_fd(s[j++], STDOUT_FILENO);
	printf("\"%s\"\n", s + j);
}

static bool	print_exports_init(char **envp, size_t *count, bool **printed,
		size_t *i)
{
	*i = 0;
	*count = 0;
	while (envp[*count])
		(*count)++;
	*printed = ft_calloc(*count, sizeof(bool));
	return (*printed != NULL);
}

static void	print_exports(char **envp)
{
	size_t	count;
	bool	*printed;
	size_t	i;
	size_t	j;
	int		min_idx;

	if (!print_exports_init(envp, &count, &printed, &i))
		return ;
	while (i < count)
	{
		min_idx = -1;
		j = -1;
		while (++j < count)
		{
			if (!printed[j] && (min_idx == -1 || ft_strncmp(envp[j],
						envp[min_idx], ft_strlen(envp[min_idx])) < 0))
				min_idx = j;
		}
		i++;
		if (min_idx == -1)
			continue ;
		printed[min_idx] = true;
		print_entry(envp[min_idx]);
	}
	free(printed);
}

int	export(int ac, char **av, char ***envp)
{
	char	**var;
	int		failures;

	if (ac <= 1 || !++av)
		return (print_exports(*envp), 0);
	failures = 0;
	while (--ac > 0)
	{
		var = var_split(*av);
		if (var && check_varname(*var))
			failures += ft_setenv(envp, var[0], var[1], var[1] != NULL);
		else
		{
			failures += 1;
			if (var)
			{
				ft_putstr_fd("export: not an identifier: ", STDERR_FILENO);
				ft_putendl_fd(*var, STDERR_FILENO);
			}
		}
		if (var)
			arr_destroy((void **)var);
		av++;
	}
	return (failures != 0);
}
