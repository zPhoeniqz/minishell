/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbindl <pbindl@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 18:13:45 by pbindl            #+#    #+#             */
/*   Updated: 2026/01/21 21:17:33 by pbindl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/path.h"
#include "libft/libft.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void	env(char **envp)
{
	char	**e;

	e = envp;
	while (*e)
		printf("%s\n", *e++);
}

static bool	reassign(char **envp, char *varname, char *value)
{
	char	**e;
	char	*newvar;
	size_t	size;
	size_t	varnamesize;

	e = envp;
	varnamesize = ft_strlen(varname);
	while (ft_strncmp(*e, varname, ft_strlen(varname) != 0))
		e++;
	if (!*e)
		return (false);
	size = varnamesize + 1 + ft_strlen(value);
	newvar = malloc(size);
	if (!newvar)
		return (false);
	free(*e);
	ft_strlcpy(newvar, varname, size);
	newvar[varnamesize] = '=';
	ft_strlcat(newvar, value, size);
	*e = newvar;
	return (true);
}

// TODO reset variables that already have been set
bool	export(char ***envp, char *varname, char *value)
{
	unsigned int	envcount;
	char			**current_envp;
	char			**new_envp;

	envcount = 0;
	current_envp = *envp;
	if (reassign(*envp, varname, value))
		return (true);
	while (current_envp[envcount])
		envcount++;
	new_envp = ft_calloc(envcount + 1, sizeof(char *));
	if (!new_envp)
		return (false);
	ft_memcpy(new_envp, current_envp, envcount);
	new_envp[envcount] = ft_strdup(varname);
	if (!new_envp[envcount])
		return (false);
	if (!reassign(new_envp, varname, value))
		return (false);
	free(current_envp);
	*envp = new_envp;
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
