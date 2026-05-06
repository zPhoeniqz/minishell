/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whuth <whuth@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 12:01:21 by whuth             #+#    #+#             */
/*   Updated: 2026/05/06 17:14:56 by whuth            ###   ########.fr       */
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

t_token				*token_init(t_ttype type, char *token, t_token *next_token);
void				token_destroy(t_token *token);
t_tl				*tl_init(void);
void				tl_destroy(t_tl *tl);
bool				ft_isdelim(char c);
t_tl				*parse(char **envp, char *src);
int					exec(t_data *data);

#endif
