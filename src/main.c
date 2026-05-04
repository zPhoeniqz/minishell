/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whuth <whuth@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/26 17:48:36 by whuth             #+#    #+#             */
/*   Updated: 2026/05/04 15:55:52 by whuth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

extern char	**environ;

static void	tl_destroy(t_tl *tl)
{
	t_token	*cur;
	t_token	*next;

	if (!tl)
		return ;
	cur = tl->tokens;
	while (cur)
	{
		next = cur->next_token;
		free(cur->token);
		free(cur);
		cur = next;
	}
	free(tl);
}

int	main(void)
{
	t_data	data;
	char	**input;
	char	*prompt;
	int		status;
	int		exit_code;

	input = NULL;
	prompt = NULL;
	exit_code = 0;
	data.envp = dup_env(environ);
	data.tokenlist = NULL;
	prompt_create(&prompt, cwd_state(UPDATE));
	while (true)
	{
		addsighandler(SIGINT, signals_forward_int, 0);
		if (ft_strncmp(cwd_state(READ), prompt, ft_strlen(prompt) - 2) != 0)
			prompt_create(&prompt, cwd_state(READ));
		status = readcommand(&input, prompt);
		if (status == 0)
			continue ;
		else if (status == -1)
			break ;
		data.tokenlist = parse(data.envp, *input);
		if (!data.tokenlist)
			continue ;
		exit_code = exec(&data);
		tl_destroy(data.tokenlist);
		free(input);
		input = NULL;
	}
	free(prompt);
	arr_destroy((void *)data.envp);
	return (exit_code);
}
