/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whuth <whuth@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 12:01:21 by whuth             #+#    #+#             */
/*   Updated: 2026/05/07 13:15:23 by whuth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#include "../libft/libft.h"
#include "builtins.h"
#include "utils.h"
#include <stdbool.h>

#define USEREXIT 256
#define EMORETOREAD 1000

typedef enum e_ttype {
  Heredoc = 'H',
  InFile = 'I',
  OutFile = 'O',
  OutFileAppend = 'o',
  Argument = 'A',
  Pipe = 'P',
} t_ttype;

typedef struct s_token {
  char *token;
  t_ttype type;
  struct s_token *next_token;
} t_token;

typedef struct s_tl {
  t_token *tokens;
  int ll;
} t_tl;

typedef struct s_data {
  t_tl *tokenlist;
  char **envp;
} t_data;

typedef struct s_redir {
  char *file;
  t_ttype type;
} t_redir;

typedef struct s_stage {
  char **argv;
  int argc;
  t_redir *redirs;
  int nredirs;
} t_stage;

t_token *token_init(t_ttype type, char *token, t_token *next_token);
void token_destroy(t_token *token);
t_tl *tl_init(void);
bool ft_isdelim(char c);
int exec(t_data *data);
void tl_destroy(t_tl *tl);

t_tl *parse(char **envp, char *src, int last_exit_code);

#endif
