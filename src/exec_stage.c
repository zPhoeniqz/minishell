/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_stage.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whuth <whuth@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/11 11:54:43 by whuth             #+#    #+#             */
/*   Updated: 2026/05/12 15:26:36 by pbindl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/exec.h"

static bool	is_redir_type(t_ttype type)
{
	return (type == InFile || type == OutFile || type == OutFileAppend
		|| type == Heredoc || type == HeredocExpand);
}

static int	argv_push(t_stage *st, int *cap, char *token)
{
	char	**tmp;

	if (st->argc < *cap - 1)
	{
		st->argv[st->argc++] = token;
		return (0);
	}
	*cap *= 2;
	tmp = ft_calloc(*cap, sizeof(char *));
	if (!tmp)
		return (-1);
	ft_memcpy(tmp, st->argv, st->argc * sizeof(char *));
	free(st->argv);
	st->argv = tmp;
	st->argv[st->argc++] = token;
	return (0);
}

static t_token	*stage_consume(t_token *cur, t_stage *st, int *cap)
{
	while (cur && cur->type != Pipe)
	{
		if (cur->type == Argument)
		{
			if (argv_push(st, cap, cur->token) == -1)
				return (free(st->argv), st->argv = NULL, NULL);
		}
		else if (is_redir_type(cur->type))
		{
			if (!push_redir(st, cur->type, cur->token))
				return (free(st->argv), st->argv = NULL, NULL);
		}
		cur = cur->next_token;
	}
	return (cur);
}

t_token	*build_stage(t_token *cur, t_stage *st)
{
	int	cap;

	ft_bzero(st, sizeof(*st));
	cap = 8;
	st->argv = ft_calloc(cap, sizeof(char *));
	if (!st->argv)
		return (NULL);
	cur = stage_consume(cur, st, &cap);
	if (!st->argv)
		return (NULL);
	st->argv[st->argc] = NULL;
	if (cur && cur->type == Pipe)
		return (cur->next_token);
	return (NULL);
}
