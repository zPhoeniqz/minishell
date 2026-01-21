/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbindl <pbindl@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 16:46:31 by pbindl            #+#    #+#             */
/*   Updated: 2026/01/15 22:49:22 by pbindl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/path.h"
#include "inc/prompt.h"
#include "inc/signals.h"
#include "libft/libft.h"
#include <linux/limits.h>
#include <stdio.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <signal.h>
#include <stdbool.h>
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

static void	arr_destroy(void **arr)
{
	char	**oarr;

	if (!arr)
		return ;
	oarr = (char **)arr;
	while (*arr)
		free(*arr++);
	free(oarr);
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
void	prompt_run(char **envp)
{
	char	*prompt;
	char	**argv;
	pid_t	pid;
	int		status;

	prompt = NULL;
      argv = NULL;
	prompt_create(&prompt, cwd_state(UPDATE));
	while (true)
	{
		addsighandler(SIGINT, signals_forward_int, 0);
		if (ft_strncmp(cwd_state(READ), prompt, ft_strlen(prompt) - 2) != 0)
			prompt_create(&prompt, cwd_state(READ));
		status = readcommand(&argv, prompt);
		if (status == 0)
			continue ; 
		else if (status == -1)
			return (cwd_state(FREE), free(prompt));
		pid = fork();
		if (pid == 0)
		{
			addsighandler(SIGINT, SIG_DFL, 0);
			if (!ft_strchr(argv[0], '/'))
				run_system_exec(argv, envp);
			else
				execve(argv[0], argv, envp);
		}
		else
		{
			addsighandler(SIGINT, SIG_IGN, 0);
			waitpid(pid, &status, 0);
		}
		arr_destroy((void **)argv);
	}
}

//*/
int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	addsighandler(SIGQUIT, SIG_IGN, 0);
	prompt_run(envp);
}
//*/
