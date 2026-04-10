/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbindl <pbindl@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 18:13:45 by pbindl            #+#    #+#             */
/*   Updated: 2026/04/10 19:08:41 by pbindl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "../inc/path.h"
#include "../inc/prompt.h"
#include "../inc/utils.h"
#include "../libft/libft.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern char	**environ;

void	env(char **envp)
{
	char	**e;

	e = envp;
	while (*e)
		printf("%s\n", *e++);
}

static int	find_var(char *varname)
{
	size_t	len;
	int		i;

	if (!varname)
		return (-2);
	len = ft_strlen(varname);
	i = 0;
	while (environ[i])
	{
		if (ft_strncmp(environ[i], varname, len) == 0)
			return (i);
		i++;
	}
	return (-1);
}

static void	assign(char **target, char *varname, char *value)
{
	size_t	name_len;
	size_t	val_len;

	name_len = ft_strlen(varname);
	val_len = ft_strlen(value);
	*target = ft_calloc(name_len + 1 + val_len + 1, 1);
	ft_memcpy(*target, varname, name_len);
	(*target)[name_len] = '=';
	ft_memcpy(*target + name_len + 1, value, val_len);
}

static bool	export_single(char *varname, char *value)
{
	char	**e;
	size_t	num_vars;
	int		idx;

	idx = find_var(varname);
	if (idx != -1)
	{
		free(environ[idx]);
		assign(environ + idx, varname, value);
		return (true);
	}
	num_vars = 0;
	while (environ[num_vars])
		num_vars++;
	e = ft_calloc(num_vars + 2, sizeof(char *));
	ft_memcpy(e, environ, num_vars * sizeof(char *));
	assign(e + num_vars, varname, value);
	environ = e;
	return (true);
}

bool	oldexport(int ac, char **av)
{
	int		i;
	char	**split_av;
	int		failures;

	failures = 0;
	i = -1;
	while (++i < ac)
	{
		if (ft_isdigit(av[i][0]))
		{
			printf("Not legit var: %s\n", av[i]);
			failures++;
			continue ;
		}
		split_av = ft_split(av[i], '=');
		if (!split_av)
		{
			failures++;
			continue ;
		}
		failures += export_single(split_av[0], split_av[1]);
		arr_destroy((void **)split_av);
	}
	return (failures == 0);
}

static bool	check_varname(const char *name)
{
	if (!ft_isalpha(*name) && *name != '_')
		return (false);
	while (*name)
	{
		if (!ft_isalnum(*name) && *name != '_')
			return (false);
		name++;
	}
	return (true);
}

bool	export(int ac, char **av)
{
	char	**var;
	int		failures;

	if (ac == 0)
		return (true);
	failures = 0;
	while (ac > 0)
	{
		var = ft_split(*av, '=');
		if (var && var[1] && check_varname(*var))
			failures += ft_setenv(var[0], var[1], true);
		else
			failures -= 1;
		if (var)
			arr_destroy((void **)var);
		ac--;
		av++;
	}
	return (failures == 0);
}

void	pwd(void)
{
	printf("%s\n", cwd_state(READ));
}

bool	unset(char *envname)
{
	int	idx;
	int	num_vars;
	int	i;

	idx = find_var(envname);
	if (idx < 0)
		return (true);
	num_vars = 0;
	while (environ[num_vars])
		num_vars++;
	free(environ[idx]);
	i = idx;
	while (i < num_vars - 2)
	{
		environ[i] = environ[i + 1];
		i++;
	}
	environ[num_vars - 2] = 0;
	return (true);
}
