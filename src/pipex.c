/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whuth <whuth@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 12:13:55 by whuth             #+#    #+#             */
/*   Updated: 2026/04/13 13:18:29 by whuth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

extern char		**environ;

void	here_doc_put_in(char **av, int *p_fd)
{
	char	*ret;

	close(p_fd[0]);
	while (1)
	{
		ret = get_next_line(0);
		if (ft_strncmp(ret, av[2], ft_strlen(av[2])) == 0)
		{
			free(ret);
			get_next_line(-1);
			exit(0);
		}
		ft_putstr_fd(ret, p_fd[1]);
		free(ret);
	}
}

void	here_doc(char **av)
{
	int		p_fd[2];
	pid_t	pid;

	if (pipe(p_fd) == -1)
		exit(0);
	pid = fork();
	if (pid == -1)
		exit(0);
	if (!pid)
		here_doc_put_in(av, p_fd);
	else
	{
		close(p_fd[1]);
		dup2(p_fd[0], 0);
		close(p_fd[0]);
		wait(NULL);
	}
}

static int	abs_fd(int fd)
{
	if (fd < 0)
		return (-fd);
	return (fd);
}

static pid_t	fork_last(int fd_out, char **av, int ac)
{
	pid_t	last;

	last = fork();
	if (!last)
	{
		dup2(fd_out, 1);
		close(fd_out);
		exec(av[ac - 2]);
	}
	return (last);
}

int	main(int ac, char **av)
{
	int		i;
	int		fd_out;
	int		n;
	pid_t	last;

	if (ac < 5)
		exit_handler(1);
	fd_out = setup(ac, av, &i);
	n = ac - i - 2;
	while (i < ac - 2)
		do_pipe(av[i++]);
	last = fork_last(abs_fd(fd_out), av, ac);
	close(abs_fd(fd_out));
	close(0);
	return (wait_children(n + 1, last, fd_out < 0));
}
