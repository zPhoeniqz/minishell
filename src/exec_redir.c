/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whuth <whuth@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/11 12:06:46 by whuth             #+#    #+#             */
/*   Updated: 2026/05/12 13:02:43 by pbindl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/exec.h"

bool	push_redir(t_stage *st, t_ttype type, char *file)
{
	t_redir	*tmp;

	tmp = ft_calloc(st->nredirs + 1, sizeof(t_redir));
	if (!tmp)
		return (false);
	if (st->redirs)
	{
		ft_memcpy(tmp, st->redirs, st->nredirs * sizeof(t_redir));
		free(st->redirs);
	}
	tmp[st->nredirs].type = type;
	tmp[st->nredirs].file = file;
	tmp[st->nredirs].fd = -1;
	st->redirs = tmp;
	st->nredirs++;
	return (true);
}

static int	apply_heredoc(t_redir *r)
{
	if (r->fd == -1)
		return (-1);
	dup2(r->fd, STDIN_FILENO);
	close(r->fd);
	r->fd = -1;
	return (0);
}

static int	apply_infile(t_redir *r)
{
	int	fd;

	fd = open(r->file, O_RDONLY);
	if (fd == -1)
		return (perror(r->file), -1);
	dup2(fd, STDIN_FILENO);
	close(fd);
	return (0);
}

int	apply_input(t_stage *st)
{
	int	i;

	i = 0;
	while (i < st->nredirs)
	{
		if (st->redirs[i].type == Heredoc
			|| st->redirs[i].type == HeredocExpand)
		{
			if (apply_heredoc(&st->redirs[i]) == -1)
				return (-1);
		}
		else if (st->redirs[i].type == InFile)
		{
			if (apply_infile(&st->redirs[i]) == -1)
				return (-1);
		}
		i++;
	}
	return (0);
}
