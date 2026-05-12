/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_outfile.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whuth <whuth@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/11 12:08:10 by whuth             #+#    #+#             */
/*   Updated: 2026/05/12 01:08:30 by whuth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/exec.h"

static int	open_outfile(t_redir *r)
{
	int	flags;

	flags = O_WRONLY | O_CREAT | O_TRUNC;
	if (r->type == OutFileAppend)
		flags = O_WRONLY | O_CREAT | O_APPEND;
	return (open(r->file, flags, 0644));
}

int	apply_output(t_stage *st)
{
	int	i;
	int	fd;

	i = 0;
	while (i < st->nredirs)
	{
		if (st->redirs[i].type == OutFile
			|| st->redirs[i].type == OutFileAppend)
		{
			fd = open_outfile(&st->redirs[i]);
			if (fd == -1)
			{
				perror(st->redirs[i].file);
				return (-1);
			}
			if (dup2(fd, STDOUT_FILENO) == -1)
			{
				close(fd);
				return (perror("dup2"), -1);
			}
			close(fd);
		}
		i++;
	}
	return (0);
}
