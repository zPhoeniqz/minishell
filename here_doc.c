#include "../inc/minishell.h"

static void	here_doc_put_in(char *in, int *p_fd)
{
	char	*ret;
	char	*del;

	close(p_fd[0]);
	del = ft_memmove(del, in, (size_t)ft_strlen(in))
	in = NULL;
	while (1)
	{
		ret = get_next_line(0);
		if (ft_strncmp(ret, del, ft_strlen(del)) == 0)
		{
			free(ret);
			get_next_line(-1);
			exit(0);
		}
		//ft_putstr_fd(ret, p_fd[1]);
		free(ret);
	}
}

static char	*here_doc(char *del)
{
	int		p_fd[2];
	pid_t	pid;

	if (pipe(p_fd) == -1)
		exit(0);
	pid = fork();
	if (pid == -1)
		exit(0);
	if (!pid)
		here_doc_put_in(del, p_fd);
	else
	{
		close(p_fd[1]);
		dup2(p_fd[0], 0);
		close(p_fd[0]);
		wait(NULL);
	}
}

void	check_here_doc(t_data data)
{
	int		i;
	t_tl	prompt;
	char

	i = 0;
	prompt = data->tokenlist;
	while (i < prompt.ll)
	{
		if (prompt->tokens.type == HEREDOC)
		{
			here_doc(prompt->tokens->token);
			prompt->tokens.type = ARGUMENT;
		}
		prompt->tokens = prompt->tokens->next_token;
		++i;
	}
}
