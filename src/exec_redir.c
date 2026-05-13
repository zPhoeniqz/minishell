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

static int	open_redir(t_redir *r)
{
	if (r->type == InFile)
		return (open(r->file, O_RDONLY));
	if (r->type == OutFile)
		return (open(r->file,
				O_WRONLY | O_CREAT | O_TRUNC, 0644));
	if (r->type == OutFileAppend)
		return (open(r->file,
				O_WRONLY | O_CREAT | O_APPEND, 0644));
	if (r->type == Heredoc || r->type == HeredocExpand)
		return (r->fd);
	return (-1);
}

int	apply_redirs(t_stage *st)
{
	int	i;
	int	fd;

	i = 0;
	while (i < st->nredirs)
	{
		fd = open_redir(&st->redirs[i]);
		if (fd < 0)
			return (perror(st->redirs[i].file), -1);
		if (st->redirs[i].type == InFile
			|| st->redirs[i].type == Heredoc
			|| st->redirs[i].type == HeredocExpand)
		{
			if (dup2(fd, STDIN_FILENO) < 0)
				return (close(fd), perror("dup2"), -1);
		}
		else if (dup2(fd, STDOUT_FILENO) < 0)
			return (close(fd), perror("dup2"), -1);
		close(fd);
		st->redirs[i].fd = -1;
		i++;
	}
	return (0);
}
