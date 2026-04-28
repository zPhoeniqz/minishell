/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whuth <whuth@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 12:01:21 by whuth             #+#    #+#             */
/*   Updated: 2026/04/28 19:23:34 by whuth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include "builtins.h"
# include "pipex.h"
# include "utils.h"
# include <stdbool.h>

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

void				gettokens(char *input, t_data *data);
int					is_paren(char c);
unsigned int		count_tokens(const char *s);
int					check_quote(char *s, size_t *elen);
int					is_del(char c);
size_t				token_len(const char *s);
char				**strarr_destruct(char **in, int n);
int					is_sep(char c);

char				*ft_strcdup(const char *s, char c);

void				free_token_list(t_tl *tl);
# endim
