/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whuth <whuth@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/26 17:48:36 by whuth             #+#    #+#             */
/*   Updated: 2026/05/08 14:40:39 by whuth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "../inc/path.h"
#include "../inc/prompt.h"
#include "../inc/signals.h"
#include <errno.h>
#include <readline/readline.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

extern char	**environ;

int	main(void)
{
	char	*prompt;
	char	*input;
	int		tmp_status;
	t_data	data;
	int		exit_code;

	prompt = NULL;
	input = NULL;
	data.envp = dup_env(environ);
	if (!data.envp)
		return (EXIT_FAILURE);
	prompt_create(&prompt, cwd_state(UPDATE));
	exit_code = 0;
	while (true)
	{
		addsighandler(SIGINT, sigfunc_redisplay_prompt, 0);
		prompt_create(&prompt, cwd_state(READ));
		tmp_status = read_cmd(&input, prompt);
		if (tmp_status == 0)
			continue ;
		else if (tmp_status == -1)
			break ;
		data.tokenlist = parse(data.envp, input, exit_code);
		free(input);
		if (errno != 0)
			exit_code = 2;
		if (data.tokenlist)
		{
			if (errno == 0)
			{
				addsighandler(SIGINT, sigfunc_return_to_prompt, 0);
				tmp_status = exec(&data, &exit_code);
			}
			tl_destroy(data.tokenlist);
		}
		if (tmp_status == USEREXIT)
			break ;
		exit_code = tmp_status % 256;
	}
	free(prompt);
	cwd_state(FREE);
	arr_destroy((void **)data.envp);
	rl_clear_history();
	return (exit_code);
}
