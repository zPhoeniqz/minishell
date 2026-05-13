/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_child.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whuth <whuth@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/11 12:03:24 by whuth             #+#    #+#             */
/*   Updated: 2026/05/13 00:16:53 by whuth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/exec.h"
#include <readline/readline.h>

static void	child_free(t_data *data, t_stage *st)
{
	free(data->prompt);
	data->prompt = NULL;
	arr_destroy((void **)data->envp);
	rl_clear_history();
	tl_destroy(data->tokenlist);
	free(st->redirs);
	free(st->argv);
	cwd_state(FREE);
}

static int	exec_external(t_stage *st, char **envp)
{
	char	*path;

	path = resolve_path(st->argv[0], envp);
	if (!path)
	{
		ft_putstr_fd(st->argv[0], STDERR_FILENO);
		ft_putstr_fd(": command not found\n", STDERR_FILENO);
		return (127);
	}
	execve(path, st->argv, envp);
	perror(st->argv[0]);
	free(path);
	return (126);
}

void	exec_child(t_stage *st, t_data *data, volatile int *exitcode)
{
	int	ret;

	if (apply_redirs(st) == -1)
	{
		child_free(data, st);
		exit(1);
	}
	if (!st->argv || !st->argv[0])
	{
		child_free(data, st);
		exit(0);
	}
	if (!is_builtin(st->argv[0]))
		ret = exec_external(st, data->envp);
	else
		ret = run_builtin(st, &data->envp, exitcode);
	child_free(data, st);
	exit(ret);
}
