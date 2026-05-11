/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_child.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whuth <whuth@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/11 12:03:24 by whuth             #+#    #+#             */
/*   Updated: 2026/05/11 14:55:10 by whuth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/exec.h"

static void	exec_external(t_stage *st, char **envp)
{
	char	*path;

	path = resolve_path(st->argv[0], envp);
	if (!path)
	{
		ft_putstr_fd(st->argv[0], STDERR_FILENO);
		ft_putstr_fd(": command not found\n", STDERR_FILENO);
		exit(127);
	}
	execve(path, st->argv, envp);
	perror(st->argv[0]);
	free(path);
	exit(126);
}

void	exec_child(t_stage *st, char **envp, int *exitcode)
{
	if (apply_input(st) == -1)
		exit(1);
	if (apply_output(st) == -1)
		exit(1);
	if (!st->argv || !st->argv[0])
		exit(0);
	if (is_builtin(st->argv[0]))
		exit(run_builtin(st, &envp, exitcode));
	exec_external(st, envp);
}
