/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whuth <whuth@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/11 11:57:03 by whuth             #+#    #+#             */
/*   Updated: 2026/05/13 16:29:28 by pbindl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/exec.h"
#include "../inc/utils.h"
#include <limits.h>

static bool	is_numeric(const char *s)
{
	ft_atoll(s);
	if (errno == EINVAL)
		return (false);
	if (*s == '-' || *s == '+')
		s++;
	if (!*s)
		return (false);
	while (*s)
	{
		if (!ft_isdigit(*s))
			return (false);
		s++;
	}
	return (true);
}

static int	handle_exit(char **envp, t_stage *st, volatile int *exitcode)
{
	int	shlvl;

	shlvl = ft_atoi(ft_getenv(envp, "SHLVL"));
	if (shlvl > 0)
		ft_putstr_fd("exit\n", STDOUT_FILENO);
	if (st->argc > 2)
	{
		ft_putendl_fd("exit: too many arguments", STDERR_FILENO);
		return (1);
	}
	if (st->argc == 2 && !is_numeric(st->argv[1]))
	{
		ft_putstr_fd("exit: ", STDERR_FILENO);
		ft_putstr_fd(st->argv[1], STDERR_FILENO);
		ft_putendl_fd(": numeric argument required", STDERR_FILENO);
		*exitcode = 2;
		return (USEREXIT);
	}
	if (st->argc == 2)
	{
		*exitcode = ft_atoi(st->argv[1]) % 256;
		if (*exitcode < 0)
			*exitcode += 256;
	}
	return (USEREXIT);
}

bool	is_builtin(const char *name)
{
	static const char	*b[] = {"echo", "cd", "pwd", "export", "unset", "env",
		"exit", NULL};
	int					i;

	i = 0;
	while (b[i])
	{
		if (ft_strncmp(name, b[i], ft_strlen(b[i]) + 1) == 0)
			return (true);
		i++;
	}
	return (false);
}

int	run_builtin(t_stage *st, char ***envp, volatile int *exitcode)
{
	const char	*n;

	errno = 0;
	n = st->argv[0];
	if (ft_strncmp(n, "echo", 5) == 0)
		return (echo(st->argc, st->argv, *envp));
	if (ft_strncmp(n, "cd", 3) == 0)
		return (cd(st->argc, st->argv, *envp));
	if (ft_strncmp(n, "pwd", 4) == 0)
		return (pwd(st->argc, st->argv, *envp), 0);
	if (ft_strncmp(n, "export", 7) == 0)
		return (export(st->argc, st->argv, envp));
	if (ft_strncmp(n, "unset", 6) == 0)
		return (unset(st->argc, st->argv, envp));
	if (ft_strncmp(n, "env", 4) == 0)
		return (env(st->argc, st->argv, *envp), 0);
	if (ft_strncmp(n, "exit", 5) == 0)
		return (handle_exit(*envp, st, exitcode));
	return (1);
}
