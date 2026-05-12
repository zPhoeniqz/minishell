/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whuth <whuth@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/13 00:37:34 by whuth             #+#    #+#             */
/*   Updated: 2026/05/13 00:42:50 by whuth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/exec.h"

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

int	pipe_loop(t_stage *stages, pid_t *pids, t_data *data,
		volatile int *exitcode)
{
	int		i;
	int		n;
	int		p[2];
	int		prev_read;
	t_stage	cur_stage;

	i = 0;
	prev_read = -1;
	n = count_stages(data->tokenlist->tokens);
	while (i < n)
	{
		if (i < n - 1 && pipe(p) == -1)
			return (perror("pipe"), -1);
		pids[i] = fork_setup();
		if (pids[i] == -1)
			return (perror("fork"), -1);
		if (pids[i] == 0)
		{
			free(pids);
			close_other_heredocs(stages, n, i);
			rescue_stage(&cur_stage, stages, i, n);
			child_setup_io(prev_read, p, i, n);
			exec_child(&cur_stage, data, exitcode);
		}
		parent_advance_pipe(&prev_read, p, i, n);
		i++;
	}
	return (0);
}
