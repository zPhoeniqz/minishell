/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whuth <whuth@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/11 12:04:37 by whuth             #+#    #+#             */
/*   Updated: 2026/05/13 20:31:57 by pbindl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/exec.h"
#include <stdio.h>
#include <readline/readline.h>
#include <sys/ioctl.h>

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
	if (ret == 130 || ret == 131)
		write(STDOUT_FILENO, "\n", 1);
	return (ret);
}

static void	parent_advance_pipe(t_pipe_iter *it)
{
	if (it->prev_read != -1)
		close(it->prev_read);
	if (it->i < it->n - 1)
	{
		close(it->p[1]);
		it->prev_read = it->p[0];
	}
}

static int	pipe_loop(t_stage *stages, pid_t *pids, t_data *data,
		volatile int *exitcode)
{
	int			i;
	int			n;
	int			p[2];
	t_pipe_iter	it;

	i = 0;
	it.prev_read = -1;
	n = count_stages(data->tokenlist->tokens);
	while (i < n)
	{
		if (i < n - 1 && pipe(p) == -1)
			return (perror("pipe"), -1);
		it.p = p;
		it.i = i;
		it.n = n;
		it.data = data;
		pids[i] = fork_setup();
		if (pids[i] == -1)
			return (perror("fork"), -1);
		if (pids[i] == 0)
			pipe_child(stages, pids, exitcode, &it);
		parent_advance_pipe(&it);
		i++;
	}
	return (0);
}

int	exec_pipeline(t_stage *stages, int n, t_data *data, volatile int *exitcode)
{
	pid_t	*pids;
	int		ret;

	pids = ft_calloc(n, sizeof(pid_t));
	if (!pids)
		return (perror("calloc"), 1);
	addsighandler(SIGINT, SIG_IGN, 0);
	if (pipe_loop(stages, pids, data, exitcode) == -1)
	{
		free(pids);
		return (1);
	}
	ret = pipe_wait_all(pids, n);
	free(pids);
	return (ret);
}
