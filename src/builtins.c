/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbindl <pbindl@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 18:13:45 by pbindl            #+#    #+#             */
/*   Updated: 2026/03/19 19:15:52 by pbindl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/path.h"
#include "../inc/prompt.h"
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

bool	export(char *varname, char *value)
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

void	pwd(void)
{
	printf("%s\n", cwd_state(READ));
}

// TODO handle cases where envname is NULL or envname cant be found
bool	unset(char ***envp, char *envname)
{
	int		envcount;
	char	*target;
	char	**current_envp;
	char	**new_envp;
	int		i;

	envcount = 0;
	target = NULL;
	current_envp = *envp;
	while (current_envp[envcount])
	{
		if (strncmp(current_envp[envcount], envname, ft_strlen(envname)) == 0)
			target = current_envp[envcount];
		envcount++;
	}
	if (!target)
		return (false);
	new_envp = ft_calloc(envcount - 1, sizeof(char *));
	if (!new_envp)
		return (false);
	printf("target; %s\n", target);
	i = 0;
	while (i < envcount - 1)
	{
		if (ft_strncmp(current_envp[i], target, ft_strlen(target)) == 0)
		{
			printf("found target\n");
			new_envp[i] = current_envp[envcount - 1];
		}
		else
			new_envp[i] = current_envp[i];
		i++;
	}
	*envp = new_envp;
	return (true);
}
