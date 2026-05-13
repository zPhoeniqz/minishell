/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whuth <whuth@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/13 11:40:52 by whuth             #+#    #+#             */
/*   Updated: 2026/05/13 11:51:45 by whuth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/exec.h"

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

static void	child_setup_io(t_pipe_iter *it)
{
	if (it->prev_read != -1)
	{
		dup2(it->prev_read, STDIN_FILENO);
		close(it->prev_read);
	}
	if (it->i < it->n - 1)
	{
		close(it->p[0]);
		dup2(it->p[1], STDOUT_FILENO);
		close(it->p[1]);
	}
}

static void	close_other_heredocs(t_stage *stages, int n, int keep)
{
	int	i;
	int	j;

	i = 0;
	while (i < n)
	{
		if (i != keep)
		{
			j = 0;
			while (j < stages[i].nredirs)
			{
				if (stages[i].redirs[j].fd != -1)
					close(stages[i].redirs[j].fd);
				j++;
			}
		}
		i++;
	}
}

void	pipe_child(t_stage *stages, pid_t *pids, volatile int *exitcode,
		t_pipe_iter *it)
{
	t_stage	cur_stage;

	free(pids);
	close_other_heredocs(stages, it->n, it->i);
	rescue_stage(&cur_stage, stages, it->i, it->n);
	child_setup_io(it);
	exec_child(&cur_stage, it->data, exitcode);
}
