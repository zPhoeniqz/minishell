/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whuth <whuth@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/26 17:48:36 by whuth             #+#    #+#             */
/*   Updated: 2026/05/13 20:37:13 by pbindl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "../inc/path.h"
#include "../inc/prompt.h"
#include "../inc/signals.h"
#include <errno.h>
#include <readline/readline.h>
#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

extern char		**environ;

volatile int	g_exit_code = 0;

static bool	init_all(char **prompt, char **input, t_data *data)
{
	*prompt = NULL;
	*input = NULL;
	data->envp = dup_env(environ);
	if (!data->envp)
		return (false);
	return (true);
}

static int	run(t_data *data, char *input, volatile int *exit_code)
{
	int	out;

	out = -1;
	data->tokenlist = parse(data->envp, input, *exit_code);
	free(input);
	if (errno != 0)
		*exit_code = 2;
	if (data->tokenlist)
	{
		if (errno == 0)
			out = exec(data, exit_code);
		tl_destroy(data->tokenlist);
	}
	return (out);
}

static void	print_exit(char **envp)
{
	int	shlvl;

	shlvl = 0;
	shlvl = ft_atoi(ft_getenv(envp, "SHLVL"));
	if (shlvl > 0)
		ft_putstr_fd("exit\n", STDOUT_FILENO);
}

static int	main_loop(t_data *data, char **prompt, char **input)
{
	int	tmp_status;

	while (true)
	{
		addsighandler(SIGINT, sigfunc_redisplay_prompt, 0);
		addsighandler(SIGQUIT, SIG_IGN, 0);
		free(*prompt);
		*prompt = NULL;
		if (!prompt_create(prompt, cwd_state(READ)))
			break ;
		tmp_status = read_cmd(input, *prompt);
		if (tmp_status == 0)
			continue ;
		if (tmp_status == -1)
		{
			print_exit(data->envp);
			break ;
		}
		data->prompt = *prompt;
		tmp_status = run(data, *input, &g_exit_code);
		if (tmp_status == USEREXIT)
			break ;
		g_exit_code = tmp_status % 256;
	}
	return (g_exit_code);
}

int	main(void)
{
	char	*prompt;
	char	*input;
	t_data	data;

	if (!init_all(&prompt, &input, &data))
		return (EXIT_FAILURE);
	main_loop(&data, &prompt, &input);
	free_all(&data, &prompt);
	return (g_exit_code);
}
