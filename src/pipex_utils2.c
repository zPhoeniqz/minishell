/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whuth <whuth@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 14:31:44 by whuth             #+#    #+#             */
/*   Updated: 2026/04/13 13:21:56 by whuth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	handle_infile(char **av, int fd_in)
{
	if (fd_in != -1)
		return (fd_in);
	ft_putstr_fd("pipex: ", 2);
	ft_putstr_fd(av[1], 2);
	ft_putendl_fd(": No such file or directory", 2);
	return (open("/dev/null", O_RDONLY));
}

static int	setup_heredoc(int ac, char **av, int *i)
{
	int	fd_out;

	if (ac < 6)
		exit_handler(1);
	*i = 3;
	fd_out = open_file(av[ac - 1], 2);
	here_doc(av);
	return (fd_out);
}

static int	setup_files(int ac, char **av)
{
	int	fd_in;
	int	fd_out;

	fd_in = open_file(av[1], 0);
	fd_out = open_file(av[ac - 1], 1);
	if (fd_out == -1)
	{
		ft_putstr_fd("pipex: ", 2);
		ft_putstr_fd(av[ac - 1], 2);
		ft_putendl_fd(": Permission denied", 2);
		fd_out = open("/dev/null", O_WRONLY);
		fd_in = handle_infile(av, fd_in);
		return (dup2(fd_in, 0), close(fd_in), -(fd_out));
	}
	fd_in = handle_infile(av, fd_in);
	return (dup2(fd_in, 0), close(fd_in), fd_out);
}

int	setup(int ac, char **av, int *i)
{
	if (ft_strncmp(av[1], "here_doc", 8) == 0)
		return (setup_heredoc(ac, av, i));
	*i = 2;
	return (setup_files(ac, av));
}

int	wait_children(int n, pid_t last, int out_err)
{
	pid_t	pid;
	int		status;
	int		ret;

	ret = 0;
	while (n-- > 0)
	{
		pid = waitpid(-1, &status, 0);
		if (pid == last && WIFEXITED(status))
			ret = WEXITSTATUS(status);
	}
	if (out_err)
		return (1);
	return (ret);
}
