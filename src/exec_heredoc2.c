/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_heredoc2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whuth <whuth@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/11 12:11:04 by whuth             #+#    #+#             */
/*   Updated: 2026/05/12 13:07:05 by pbindl           ###   ########.fr       */
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

int	resolve_heredocs(t_stage *stages, int n, t_heredoc_ctx *ctx)
{
	int	i;
	int	j;

	i = 0;
	while (i < n)
	{
		j = 0;
		while (j < stages[i].nredirs)
		{
			if (stages[i].redirs[j].type == Heredoc
				|| stages[i].redirs[j].type == HeredocExpand)
			{
				if (resolve_heredoc(&stages[i].redirs[j], ctx) == -1)
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

void	heredoc_cleanup(t_heredoc_ctx *ctx)
{
	get_next_line(-1);
	close_heredoc_fds(ctx->stages, ctx->n);
	free_stages(ctx->stages, ctx->n);
	tl_destroy(ctx->data->tokenlist);
	arr_destroy((void **)ctx->data->envp);
	cwd_state(FREE);
	free(ctx->data->prompt);
}
