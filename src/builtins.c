/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbindl <pbindl@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 18:13:45 by pbindl            #+#    #+#             */
/*   Updated: 2026/05/11 23:48:13 by pbindl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/builtins.h"
#include "../inc/minishell.h"
#include "../inc/path.h"
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
	{
		if (ft_strchr(*e, '='))
			printf("%s\n", *e);
		e++;
	}
}

void	pwd(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;
	(void)envp;
	printf("%s\n", cwd_state(READ));
}

int	unset(int ac, char **av, char ***envp)
{
	int	i;
	int	idx;
	int	num_vars;

	i = 1;
	while (i < ac)
	{
		idx = find_var(*envp, av[i++]);
		if (idx < 0)
			continue ;
		num_vars = 0;
		while ((*envp)[num_vars])
			num_vars++;
		free((*envp)[idx]);
		while (idx < num_vars - 1)
		{
			(*envp)[idx] = (*envp)[idx + 1];
			idx++;
		}
		(*envp)[num_vars - 1] = 0;
	}
	return (0);
}

int	echo(int ac, char **av, char **envp)
{
	int		i;
	bool	nl;
	char	*s;

	(void)envp;
	if (ac <= 1)
		return (printf("\n"), 0);
	nl = true;
	i = 1;
	while (i < ac && ft_strncmp(av[i], "-n", 2) == 0)
	{
		s = ft_strrchr(av[i], 'n');
		if (!s || !ft_isdelim(s[1]))
			break ;
		nl = false;
		i++;
	}
	while (i < ac - 1)
		printf("%s ", av[i++]);
	if (i < ac)
		printf("%s", av[i]);
	if (nl)
		printf("\n");
	return (0);
}

int	cd(int ac, char **av, char **envp)
{
	if (ac < 2)
		return (0);
	if (ac > 2)
		return (ft_putendl_fd("cd: too many arguments", STDERR_FILENO), 1);
	if (chdir(av[1]) < 0)
	{
		perror("cd");
		return (1);
	}
	ft_setenv(&envp, "PWD", av[1], true);
	cwd_state(UPDATE);
	return (0);
}
