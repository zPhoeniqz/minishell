/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whuth <whuth@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/11 12:04:37 by whuth             #+#    #+#             */
/*   Updated: 2026/05/11 12:06:36 by whuth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/exec.h"

static int	pipe_wait_all(pid_t *pids, int n)
{
	int	status;
	int	ret;
	int	i;

	ret = 0;
	i = 0;
	while (i < n)
	{
		waitpid(pids[i], &status, 0);
		if (i == n - 1)
		{
			if (WIFEXITED(status))
				ret = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				ret = 128 + WTERMSIG(status);
		}
		i++;
	}
	return (ret);
}

static void	child_setup_io(int prev_read, int *p, int i, int n)
{
	if (prev_read != -1)
	{
		dup2(prev_read, STDIN_FILENO);
		close(prev_read);
	}
	if (i < n - 1)
	{
		close(p[0]);
		dup2(p[1], STDOUT_FILENO);
		close(p[1]);
	}
}

static void	parent_advance_pipe(int *prev_read, int *p, int i, int n)
{
	if (*prev_read != -1)
		close(*prev_read);
	if (i < n - 1)
	{
		close(p[1]);
		*prev_read = p[0];
	}
}

static int	pipe_loop(t_stage *stages, pid_t *pids, int n, char **envp)
{
	int	prev_read;
	int	p[2];
	int	i;

	prev_read = -1;
	i = 0;
	while (i < n)
	{
		if (i < n - 1 && pipe(p) == -1)
			return (perror("pipe"), -1);
		pids[i] = fork_setup();
		if (pids[i] == -1)
			return (perror("fork"), -1);
		if (pids[i] == 0)
		{
			child_setup_io(prev_read, p, i, n);
			exec_child(&stages[i], envp);
		}
		parent_advance_pipe(&prev_read, p, i, n);
		i++;
	}
	return (0);
}

int	exec_pipeline(t_stage *stages, int n, char **envp)
{
	pid_t	*pids;
	int		ret;

	pids = ft_calloc(n, sizeof(pid_t));
	if (!pids)
		return (perror("calloc"), 1);
	if (pipe_loop(stages, pids, n, envp) == -1)
	{
		free(pids);
		return (1);
	}
	ret = pipe_wait_all(pids, n);
	free(pids);
	return (ret);
}
