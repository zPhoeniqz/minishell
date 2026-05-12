/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whuth <whuth@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/11 11:32:17 by whuth             #+#    #+#             */
/*   Updated: 2026/05/12 00:14:39 by whuth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "gnl.h"
# include "minishell.h"
# include "path.h"
# include "signals.h"
# include <errno.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
#include <sys/wait.h>
# include <unistd.h>

typedef struct s_redir
{
	char	*file;
	t_ttype	type;
	int		fd;
}			t_redir;

typedef struct s_stage
{
	char	**argv;
	int		argc;
	t_redir	*redirs;
	int		nredirs;
}			t_stage;

typedef struct s_heredoc_ctx
{
	t_data	*data;
	t_stage	*stages;
	int		n;
	int		write_fd;
}			t_heredoc_ctx;

int			count_stages(t_token *cur);
t_token		*build_stage(t_token *cur, t_stage *st);
void		free_stages(t_stage *stages, int n);

bool		push_redir(t_stage *st, t_ttype type, char *file);
int			apply_input(t_stage *st);
int			apply_output(t_stage *st);

int			resolve_heredocs(t_stage *stages, int n, t_heredoc_ctx *ctx);
int			resolve_heredoc(t_redir *r, t_heredoc_ctx *ctx);
void		close_heredoc_fds(t_stage *stages, int n);
void		heredoc_cleanup(t_heredoc_ctx *ctx);

pid_t		fork_setup(void);
char		*resolve_path(const char *name, char **envp);
void		exec_child(t_stage *st, char **envp, int *exitcode);

bool		is_builtin(const char *name);
int			run_builtin(t_stage *st, char ***envp, int *exitcode);
int			exec_single(t_stage *st, char ***envp, int *exitcode);

int			exec_pipeline(t_stage *stages, int n, t_data *data, int *exitcode);

#endif
