/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whuth <whuth@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 12:14:36 by whuth             #+#    #+#             */
/*   Updated: 2026/04/13 13:18:56 by whuth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

extern char	**environ;

int	open_file(char *file, int in_or_out)
{
	int	ret;

	if (in_or_out == 0)
		ret = open(file, O_RDONLY, 0777);
	else if (in_or_out == 1)
		ret = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	else
		ret = open(file, O_WRONLY | O_CREAT | O_APPEND, 0777);
	return (ret);
}

void	ft_free_tab(char **tab)
{
	size_t	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

char	*my_getenv(char *name)
{
	int		i;
	int		j;
	char	*sub;

	i = 0;
	while (environ[i])
	{
		j = 0;
		while (environ[i][j] && environ[i][j] != '=')
			j++;
		sub = ft_substr(environ[i], 0, j);
		if (ft_strncmp(sub, name, ft_strlen(sub)) == 0)
		{
			free(sub);
			return (environ[i] + j + 1);
		}
		free(sub);
		i++;
	}
	return (NULL);
}

static char	*find_in_path(char **allpath, char *cmd)
{
	int		i;
	char	*part;
	char	*exec;

	i = -1;
	while (allpath[++i])
	{
		part = ft_strjoin(allpath[i], "/");
		exec = ft_strjoin(part, cmd);
		free(part);
		if (access(exec, F_OK | X_OK) == 0)
			return (exec);
		free(exec);
	}
	return (NULL);
}

char	*get_path(char *cmd)
{
	char	**allpath;
	char	**s_cmd;
	char	*exec;

	if (!cmd || !*cmd)
		return (NULL);
	s_cmd = ft_split(cmd, ' ');
	if (!s_cmd || !s_cmd[0] || !*s_cmd[0])
		return (ft_free_tab(s_cmd), NULL);
	allpath = ft_split(my_getenv("PATH"), ':');
	exec = find_in_path(allpath, s_cmd[0]);
	ft_free_tab(allpath);
	ft_free_tab(s_cmd);
	return (exec);
}
