/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbindl <pbindl@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 18:13:45 by pbindl            #+#    #+#             */
/*   Updated: 2026/04/15 15:13:09 by pbindl           ###   ########.fr       */
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
#include <unistd.h>

void	env(int ac, char **av, char **envp)
{
	char	**e;

	(void)ac;
	(void)av;
	e = envp;
	while (*e)
		printf("%s\n", *e++);
}

static int	find_var(char **envp, char *varname)
{
	size_t	len;
	int		i;

	if (!varname)
		return (-2);
	len = ft_strlen(varname);
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], varname, len) == 0)
			return (i);
		i++;
	}
	return (-1);
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

int	export(int ac, char **av, char **envp)
{
	char	**var;
	int		failures;

	if (ac <= 1)
		return (true);
	failures = 0;
	av++;
	while (ac > 1)
	{
		var = ft_split(*av, '=');
		if (var && var[1] && check_varname(*var))
			failures += ft_setenv(envp, var[0], var[1], true);
		else
			failures += 1;
		if (var)
			arr_destroy((void **)var);
		ac--;
		av++;
	}
	return (failures);
}

void	pwd(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;
	(void)envp;
	printf("%s\n", cwd_state(READ));
}

static void	unset_single(char **envp, char *envname)
{
	int	idx;
	int	num_vars;
	int	i;

	idx = find_var(envp, envname);
	if (idx < 0)
		return ;
	num_vars = 0;
	while (envp[num_vars])
		num_vars++;
	free(envp[idx]);
	i = idx;
	while (i < num_vars - 2)
	{
		envp[i] = envp[i + 1];
		i++;
	}
	envp[num_vars - 2] = 0;
}

int	unset(int ac, char **av, char **envp)
{
	int	i;

	i = 1;
	while (i < ac)
		unset_single(envp, av[i++]);
	return (0);
}

int	echo(int ac, char **av, char **envp)
{
	int		i;
	bool	nl;

	(void)envp;
	if (ac <= 1)
	{
		printf("\n");
		return (0);
	}
	nl = true;
	i = 1;
	if (ft_strncmp(av[1], "-n", ft_strlen(av[1])) == 0)
		nl = false;
	i++;
	while (i < ac - 1)
		printf("%s ", av[i++]);
	printf("%s", av[i]);
	if (nl)
		printf("\n");
	return (0);
}

int	cd(int ac, char **av, char **envp)
{
	if (ac != 2)
		return (1);
	if (chdir(av[1]) < 0)
	{
		perror(NULL);
		return (1);
	}
	ft_setenv(envp, "PWD", av[1], true);
	cwd_state(UPDATE);
	return (0);
}
