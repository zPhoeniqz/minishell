/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whuth <whuth@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 13:19:10 by whuth             #+#    #+#             */
/*   Updated: 2026/04/13 13:21:43 by whuth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

extern char	**environ;

void	exit_handler(int n_exit)
{
	if (n_exit == 1)
		ft_putstr_fd("./pipex infile cmd cmd outfile\n", 2);
	exit(0);
}

void	exec(char *cmd)
{
	char	**s_cmd;
	char	*path;

	if (!cmd || !*cmd)
	{
		ft_putstr_fd("pipex: command not found\n", 2);
		exit(127);
	}
	s_cmd = ft_split(cmd, ' ');
	path = get_path(s_cmd[0]);
	if (!path)
	{
		ft_putstr_fd("pipex: command not found: ", 2);
		ft_putendl_fd(s_cmd[0], 2);
		ft_free_tab(s_cmd);
		exit(127);
	}
	if (execve(path, s_cmd, environ) == -1)
	{
		ft_putstr_fd("pipex: command not found: ", 2);
		ft_putendl_fd(s_cmd[0], 2);
		ft_free_tab(s_cmd);
		exit(127);
	}
}

void	do_pipe(char *cmd)
{
	pid_t	pid;
	int		p_fd[2];

	if (pipe(p_fd) == -1)
		exit(0);
	pid = fork();
	if (pid == -1)
		exit(0);
	if (!pid)
	{
		close(p_fd[0]);
		dup2(p_fd[1], 1);
		close(p_fd[1]);
		exec(cmd);
	}
	else
	{
		close(p_fd[1]);
		dup2(p_fd[0], 0);
		close(p_fd[0]);
	}
}
