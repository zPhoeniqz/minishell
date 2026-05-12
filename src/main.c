/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whuth <whuth@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/26 17:48:36 by whuth             #+#    #+#             */
/*   Updated: 2026/05/12 16:45:18 by pbindl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "../inc/path.h"
#include "../inc/prompt.h"
#include "../inc/signals.h"
#include <errno.h>
#include <stdio.h>
#include <readline/readline.h>
#include <signal.h>
#include <stdbool.h>
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
	if (!prompt_create(prompt, cwd_state(UPDATE)))
		return (arr_destroy((void **)data->envp), false);
	return (true);
}

static void	free_all(t_data *data, char **prompt, bool truly_all)
{
      if(truly_all)
            free(*prompt);
      *prompt = NULL;
      if(truly_all)
            cwd_state(FREE);
      if(truly_all)
            arr_destroy((void **)data->envp);
	rl_clear_history();
}

static int	run(t_data *data, char *input, volatile int *exit_code)
{
	int	out;

	out = -1;
	data->tokenlist = parse(data->envp, input, *exit_code);
	free(data->prompt);
      free(input);
      data->prompt = NULL;
	if (errno != 0)
		*exit_code = 2;
	if (data->tokenlist)
	{
		if (errno == 0)
		{
			addsighandler(SIGINT, sigfunc_return_to_prompt, 0);
			out = exec(data, exit_code);
		}
		tl_destroy(data->tokenlist);
	}
	return (out);
}

void	handle_shlvl(char **envp)
{
	int	exit_code;

	exit_code = ft_atoi(ft_getenv(envp, "SHLVL"));
	if (exit_code > 0)
		ft_putstr_fd("exit\n", STDOUT_FILENO);
}

int	main(void)
{
	char	*prompt;
	char	*input;
	int		tmp_status;
	t_data	data;

	if (!init_all(&prompt, &input, &data))
		return (EXIT_FAILURE);
	while (true)
	{
		addsighandler(SIGINT, sigfunc_redisplay_prompt, 0);
		prompt_create(&prompt, cwd_state(READ));
		tmp_status = read_cmd(&input, prompt);
		if (tmp_status == 0)
			continue ;
		else if (tmp_status == -1)
			break ;
		data.prompt = prompt;
		tmp_status = run(&data, input, &g_exit_code);
		if (tmp_status == USEREXIT)
			break ;
		g_exit_code = tmp_status % 256;
            free_all(&data, &prompt, false);
	}
	return (handle_shlvl(data.envp), free_all(&data, &prompt, true), g_exit_code);
}
