/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_heredoc2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whuth <whuth@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/11 12:11:04 by whuth             #+#    #+#             */
/*   Updated: 2026/05/11 13:05:03 by whuth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/exec.h"

void	close_heredoc_fds(t_stage *stages, int n)
{
	int	i;
	int	j;

	i = 0;
	while (i < n)
	{
		j = 0;
		while (j < stages[i].nredirs)
		{
			if (stages[i].redirs[j].fd != -1)
			{
				close(stages[i].redirs[j].fd);
				stages[i].redirs[j].fd = -1;
			}
			j++;
		}
		i++;
	}
}

int	resolve_heredocs(t_stage *stages, int n)
{
	int	i;
	int	j;

	i = 0;
	while (i < n)
	{
		j = 0;
		while (j < stages[i].nredirs)
		{
			if (stages[i].redirs[j].type == Heredoc)
			{
				if (resolve_heredoc(&stages[i].redirs[j]) == -1)
				{
					close_heredoc_fds(stages, n);
					return (-1);
				}
			}
			j++;
		}
		i++;
	}
	return (0);
}
