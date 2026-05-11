/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbindl <pbindl@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 16:46:31 by pbindl            #+#    #+#             */
/*   Updated: 2026/05/10 21:42:27 by pbindl           ###   ########.fr       */
/*   Updated: 2026/04/15 14:43:32 by pbindl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include <linux/limits.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

char	*prompt_create(char **buf, const char *path)
{
	free(*buf);
	*buf = ft_strjoin(path, "> ");
	return (*buf);
}

int	read_cmd(char **target_buf, char *prompt)
{
	char	*input;

	input = readline(prompt);
	if (!input)
		return (-1);
	if (ft_strlen(input) < 1)
		return (0);
	add_history(input);
	*target_buf = input;
	return (1);
}

/*/
int	main(int argc, char **argv, char **envp)
{
		(void)argc;
		(void)argv;
		addsighandler(SIGQUIT, SIG_IGN, 0);
		prompt_run(envp);
}
//*/
