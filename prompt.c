/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbindl <pbindl@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 16:46:31 by pbindl            #+#    #+#             */
/*   Updated: 2026/01/13 19:26:15 by pbindl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/path.h"
#include "inc/prompt.h"
#include "libft/libft.h"
#include <linux/limits.h>
#include <readline/history.h>
#include <readline/readline.h>
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
	pid_t	pid;
	int		status;
	char	*cur_file_path;
	char	**path;
	char	**opath;

	pid = fork();
	if (pid > 0)
	{
		waitpid(pid, &status, 0);
		return (true);
	}
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

static char	**readcommand(char *prompt)
{
	char	*input;
	char	**argv;

	input = readline(prompt);
	if (!input || ft_strlen(input) < 1)
		return (NULL);
	argv = ft_split(input, ' ');
	add_history(input);
	free(input);
	return (argv);
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
	prompt_create(&prompt, cwd_state(UPDATE));
	while (true)
	{
		if (ft_strncmp(cwd_state(READ), prompt, ft_strlen(prompt) - 2) != 0)
			prompt_create(&prompt, cwd_state(READ));
		argv = readcommand(prompt);
		if (!argv || !ft_strchr(argv[0], '/'))
		{
			if (!argv || !run_system_exec(argv, envp))
				return (free(prompt), cwd_state(FREE),
					arr_destroy((void **)argv));
			continue ;
		}
		pid = fork();
		if (pid == 0)
			execve(argv[0], argv, envp);
		else
			waitpid(pid, &status, 0);
		arr_destroy((void **)argv);
	}
}

//*/
int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	prompt_run(envp);
}
//*/
