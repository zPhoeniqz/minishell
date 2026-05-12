/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whuth <whuth@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/11 12:00:36 by whuth             #+#    #+#             */
/*   Updated: 2026/05/12 16:48:35 by pbindl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/exec.h"
#include <signal.h>

pid_t	fork_setup(void)
{
	pid_t	out;

	out = fork();
	if (out == 0)
		addsighandler(SIGINT, SIG_DFL, 0);
	else
		addsighandler(SIGINT, sigfunc_return_to_prompt, 0);
	return (out);
}

static char	*get_path_val(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			return (envp[i] + 5);
		i++;
	}
	return (NULL);
}

static char	*search_dirs(char **dirs, const char *name)
{
	char	*candidate;
	int		i;

	i = 0;
	while (dirs[i])
	{
		candidate = pathjoin(dirs[i], name);
		if (candidate && access(candidate, X_OK) == 0)
			return (candidate);
		free(candidate);
		i++;
	}
	return (NULL);
}

char	*resolve_path(const char *name, char **envp)
{
	char	*path_val;
	char	**dirs;
	char	*result;

	if (!name || !*name)
		return (NULL);
	if (ft_strchr(name, '/'))
	{
		if (access(name, X_OK) == 0)
			return (ft_strdup(name));
		return (NULL);
	}
	path_val = get_path_val(envp);
	if (!path_val)
		return (NULL);
	dirs = ft_split(path_val, ':');
	if (!dirs)
		return (NULL);
	result = search_dirs(dirs, name);
	arr_destroy((void **)dirs);
	return (result);
}
