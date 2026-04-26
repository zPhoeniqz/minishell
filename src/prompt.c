/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbindl <pbindl@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 16:46:31 by pbindl            #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2026/04/26 18:02:25 by whuth            ###   ########.fr       */
=======
/*   Updated: 2026/04/15 14:43:32 by pbindl           ###   ########.fr       */
>>>>>>> master
/*                                                                            */
/* ************************************************************************** */

#include "../inc/path.h"
#include "../inc/prompt.h"
#include "../inc/signals.h"
#include "../inc/utils.h"
#include "../libft/libft.h"
#include <linux/limits.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

static char	*prompt_create(char **buf, const char *path)
{
	free(*buf);
	*buf = ft_strjoin(path, "> ");
	return (*buf);
}

static bool	run_system_exec(char **argv, char **envp)
{
	char	*cur_file_path;
	char	**path;
	char	**opath;

	path = ft_split(getenv("PATH"), ':');
	opath = path;
	while (path)
	{
		cur_file_path = pathjoin(*path, argv[0]);
		if (!cur_file_path)
			return (false);
		execve(cur_file_path, argv, envp);
		free(cur_file_path);
		path++;
	}
	arr_destroy((void **)opath);
	return (false);
}

static int	readcommand(char ***target_buf, char *prompt)
{
	char	*input;
	char	**argv;

	input = readline(prompt);
	if (!input)
		return (-1);
	if (ft_strlen(input) < 1)
		return (0);
	argv = ft_split(input, ' ');
	add_history(input);
	free(input);
	*target_buf = argv;
	return (1);
}

// TODO error handling of readline, ft_split, etc.
// TODO handle executables that are in PATH

/*/
int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	addsighandler(SIGQUIT, SIG_IGN, 0);
	prompt_run(envp);
}
//*/
