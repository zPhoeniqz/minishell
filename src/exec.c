/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whuth <whuth@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 18:17:18 by whuth             #+#    #+#             */
/*   Updated: 2026/05/11 11:54:28 by whuth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/exec.h"
#include "../libft/libft.h"
#include <stdio.h>
#include <stdlib.h>

static int	count_stages(t_token *cur)
{
	int	n;

	n = 1;
	while (cur)
	{
		if (cur->type == Pipe)
			n++;
		cur = cur->next_token;
	}
	return (n);
}

static void	free_stages(t_stage *stages, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		free(stages[i].argv);
		i++;
	}
	free(stages);
}

static int	build_all_stages(t_token *cur, t_stage *stages, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		cur = build_stage(cur, &stages[i]);
		if (!stages[i].argv)
		{
			free_stages(stages, i);
			return (-1);
		}
		i++;
	}
	return (0);
}

int	exec(t_data *data)
{
	t_stage	*stages;
	int		n;
	int		ret;

	if (!data || !data->tokenlist || !data->tokenlist->tokens)
		return (0);
	n = count_stages(data->tokenlist->tokens);
	stages = ft_calloc(n, sizeof(t_stage));
	if (!stages)
		return (perror("calloc"), 1);
	if (build_all_stages(data->tokenlist->tokens, stages, n) == -1)
		return (1);
	if (resolve_heredocs(stages, n) == -1)
	{
		free_stages(stages, n);
		return (1);
	}
	if (n == 1)
		ret = exec_single(&stages[0], &data->envp);
	else
		ret = exec_pipeline(stages, n, data->envp);
	close_heredoc_fds(stages, n);
	free_stages(stages, n);
	return (ret);
}
