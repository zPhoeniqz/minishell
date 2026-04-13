/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whuth <whuth@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 12:12:33 by whuth             #+#    #+#             */
/*   Updated: 2026/04/13 13:23:49 by whuth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/libft.h"
# include "gnl.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>
# include <unistd.h>

void	here_doc(char **av);
void	exit_handler(int n_exit);
int		open_file(char *file, int n);
char	*my_getenv(char *name);
char	*get_path(char *cmd);
void	exec(char *cmd);
void	ft_free_tab(char **tab);
int		setup(int ac, char **av, int *i);
int		wait_children(int n, pid_t last, int out_err);
void	do_pipe(char *cmd);

#endif
