/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whuth <whuth@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/26 17:48:36 by whuth             #+#    #+#             */
/*   Updated: 2026/05/11 15:15:30 by whuth            ###   ########.fr       */
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

extern char	**environ;

static bool	init_all(char **prompt, char **input, t_data *data, int *exit_code)
{
	*prompt = NULL;
	*input = NULL;
	data->envp = dup_env(environ);
	if (!data->envp)
		return (false);
	if (!prompt_create(prompt, cwd_state(UPDATE)))
		return (arr_destroy((void **)data->envp), false);
	*exit_code = 0;
	return (true);
}

static void	free_all(t_data *data, char *prompt)
{
	free(prompt);
	cwd_state(FREE);
	arr_destroy((void **)data->envp);
	rl_clear_history();
}

static int	run(t_data *data, char *input, int *exit_code)
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
		{
			addsighandler(SIGINT, sigfunc_return_to_prompt, 0);
			out = exec(data, exit_code);
		}
		tl_destroy(data->tokenlist);
	}
	return (out);
}

int	main(void)
{
	char	*prompt;
	char	*input;
	int		tmp_status;
	t_data	data;
	int		exit_code;

	if (!init_all(&prompt, &input, &data, &exit_code))
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
		tmp_status = run(&data, input, &exit_code);
		if (tmp_status == USEREXIT)
			break ;
		exit_code = tmp_status % 256;
	}
	return (free_all(&data, prompt), exit_code);
}
