/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_single.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whuth <whuth@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/11 11:58:34 by whuth             #+#    #+#             */
/*   Updated: 2026/05/11 15:11:41 by whuth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/exec.h"

static void	restore_fds(int saved_in, int saved_out)
{
	dup2(saved_in, STDIN_FILENO);
	dup2(saved_out, STDOUT_FILENO);
	close(saved_in);
	close(saved_out);
}

static int	exec_builtin_with_redirs(t_stage *st, char ***envp, int *exitcode)
{
	int	saved_in;
	int	saved_out;
	int	ret;

	saved_in = dup(STDIN_FILENO);
	saved_out = dup(STDOUT_FILENO);
	if (apply_redirs(st) == -1)
	{
		restore_fds(saved_in, saved_out);
		return (1);
	}
	ret = run_builtin(st, envp, exitcode);
	restore_fds(saved_in, saved_out);
	return (ret);
}

static int	wait_child(pid_t pid)
{
	int	status;

	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (1);
}

int	exec_single(t_stage *st, char ***envp, int *exitcode)
{
	pid_t	pid;

	if (!st->argv || !st->argv[0])
		return (0);
	if (is_builtin(st->argv[0]))
		return (exec_builtin_with_redirs(st, envp, exitcode));
	pid = fork_setup();
	if (pid == -1)
		return (perror("fork"), 1);
	if (pid == 0)
		exec_child(st, *envp, exitcode);
	return (wait_child(pid));
}
