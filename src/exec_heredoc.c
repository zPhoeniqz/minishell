/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whuth <whuth@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/11 12:09:28 by whuth             #+#    #+#             */
/*   Updated: 2026/05/12 13:06:20 by pbindl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/exec.h"

static void	heredoc_warning(char *delim)
{
	ft_putchar_fd('\n', STDOUT_FILENO);
	ft_putstr_fd("warning: here-document delimited by end-of-file (wanted `",
		STDERR_FILENO);
	ft_putstr_fd(delim, STDERR_FILENO);
	ft_putendl_fd("')", STDERR_FILENO);
}

static bool	is_delim_line(char *line, char *delim, size_t dlen)
{
	return (ft_strncmp(line, delim, dlen) == 0 && (line[dlen] == '\n'
			|| line[dlen] == '\0'));
}

static int	handle_heredoc_line(char *line, t_redir *redir, size_t dlen,
		t_heredoc_ctx *ctx)
{
	if (is_delim_line(line, redir->file, dlen))
	{
		free(line);
		return (1);
	}
	if (redir->type == HeredocExpand)
		expand_str(ctx->data->envp, &line, g_exit_code);
	ft_putstr_fd(line, ctx->write_fd);
	free(line);
	return (0);
}

static void	heredoc_child(int write_fd, t_redir *redir, t_heredoc_ctx *ctx)
{
	char	*line;
	size_t	dlen;

	dlen = ft_strlen(redir->file);
	ctx->write_fd = write_fd;
	while (1)
	{
		write(STDERR_FILENO, "> ", 2);
		line = get_next_line(STDIN_FILENO);
		if (!line)
		{
			if (errno == 0)
				heredoc_warning(redir->file);
			break ;
		}
		if (handle_heredoc_line(line, redir, dlen, ctx))
			break ;
	}
	close(write_fd);
	heredoc_cleanup(ctx);
	exit(0);
}

int	resolve_heredoc(t_redir *r, t_heredoc_ctx *ctx)
{
	int		p[2];
	pid_t	pid;

	if (pipe(p) == -1)
		return (perror("pipe"), -1);
	pid = fork();
	if (pid == -1)
		return (perror("fork"), -1);
	if (pid == 0)
	{
		addsighandler(SIGINT, SIG_DFL, 0);
		close(p[0]);
		heredoc_child(p[1], r, ctx);
	}
	close(p[1]);
	waitpid(pid, NULL, 0);
	r->fd = p[0];
	return (0);
}
