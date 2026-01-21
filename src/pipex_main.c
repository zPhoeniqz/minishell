/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whuth <whuth@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 12:13:55 by whuth             #+#    #+#             */
/*   Updated: 2025/12/19 12:16:38 by whuth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_exit(void)
{
	perror("Error");
	exit(EXIT_FAILURE);
}

void	ft_exit_file(char *file)
{
	ft_putstr_fd("Error: ", 2);
	ft_putstr_fd(file, 2);
	perror(" ");
	exit(EXIT_FAILURE);
}

void	child(char **av, char **envp, int *fd)
{
	int	fin_fd;

	close(fd[0]);
	fin_fd = open(av[1], O_RDONLY);
	if (fin_fd == -1)
		ft_exit_file(av[1]);
	else
	{
		dup2(fin_fd, STDIN_FILENO);
		close(fin_fd);
	}
	dup2(fd[1], STDOUT_FILENO);
	close(fd[1]);
	pipex(av[2], envp);
}

void	parent(char **av, char **envp, int *fd)
{
	int	fout_fd;

	close(fd[1]);
	fout_fd = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fout_fd == -1)
		ft_exit_file(av[4]);
	else
	{
		dup2(fout_fd, STDOUT_FILENO);
		close(fout_fd);
	}
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	pipex(av[3], envp);
}

int	main(int ac, char **av, char **envp)
{
	int		fd[2];
	pid_t	pid;

	if (ac != 5)
		exit(EXIT_FAILURE);
	if (pipe(fd) == -1)
		ft_exit();
	pid = fork();
	if (pid == -1)
		ft_exit();
	else if (pid == 0)
		child(av, envp, fd);
	waitpid(pid, NULL, 0);
	parent(av, envp, fd);
	return (EXIT_SUCCESS);
}
