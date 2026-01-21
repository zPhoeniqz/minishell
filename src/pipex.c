/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whuth <whuth@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 12:14:36 by whuth             #+#    #+#             */
/*   Updated: 2025/12/19 12:14:54 by whuth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	pipex(char *arg, char **envp)
{
	char	*cmd[4];

	cmd[0] = "/bin/sh";
	cmd[1] = "-c";
	cmd[2] = arg;
	cmd[3] = NULL;
	execve("/bin/sh", cmd, envp);
	perror("Error");
	exit(126);
}
