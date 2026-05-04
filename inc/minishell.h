/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whuth <whuth@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 12:01:21 by whuth             #+#    #+#             */
/*   Updated: 2026/05/04 15:13:57 by whuth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include "builtins.h"
# include "gnl.h"
# include "path.h"
# include "prompt.h"
# include "signals.h"
# include "utils.h"
# include <stdbool.h>
# include <stdio.h>

# define DEL " \t\n\r\v\f"

typedef enum e_ttype
{
	Heredoc,
	InFile,
	OutFile,
	OutFileAppend,
	Argument,
	Pipe
}					t_ttype;

typedef struct s_token
{
	char			*token;
	t_ttype			type;
	struct s_token	*next_token;
}					t_token;

typedef struct s_tl
{
	t_token			*tokens;
	int				ll;
}					t_tl;

typedef struct s_data
{
	t_tl			*tokenlist;
	char			**envp;
}					t_data;

typedef struct s_stage
{
	char			**argv;
	int				argc;
	char			*in_file;
	char			*out_file;
	char			*heredoc;
	bool			append;
}					t_stage;

t_tl				*parse(char **envp, char *src);
int					exec(t_data *data);

#endif
