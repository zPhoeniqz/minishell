/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whuth <whuth@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/11 12:04:37 by whuth             #+#    #+#             */
/*   Updated: 2026/05/13 00:38:07 by whuth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/exec.h"
#include <stdbool.h>

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

void	rescue_stage(t_stage *target, t_stage *stages, int idx, int n)
{
	int	i;

	i = -1;
	while (++i < n)
	{
		if (i == idx)
		{
			target->redirs = stages[i].redirs;
			target->nredirs = stages[i].nredirs;
			target->argv = stages[i].argv;
			target->argc = stages[i].argc;
			continue ;
		}
		free(stages[i].argv);
		free(stages[i].redirs);
	}
	free(stages);
}

int	exec_pipeline(t_stage *stages, int n, t_data *data, volatile int *exitcode)
{
	pid_t	*pids;
	int		ret;

	pids = ft_calloc(n, sizeof(pid_t));
	if (!pids)
		return (perror("calloc"), 1);
	if (pipe_loop(stages, pids, data, exitcode) == -1)
	{
		free(pids);
		return (1);
	}
	ret = pipe_wait_all(pids, n);
	free(pids);
	return (ret);
}
