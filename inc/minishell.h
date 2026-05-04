/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whuth <whuth@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 12:01:21 by whuth             #+#    #+#             */
/*   Updated: 2026/04/26 17:55:51 by whuth            ###   ########.fr       */
/*   Updated: 2026/03/26 19:51:48 by pbindl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#include "../libft/libft.h"
#include "pipex.h"
#include "builtins.h"
#include "utils.h"
#include <stdbool.h>

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

t_token *token_init(t_ttype type, char *token, t_token *next_token);
void token_destroy(t_token *token);

t_tl *tl_init();
void tl_destroy(t_tl *tl);

bool ft_isdelim(char c);

// replaces the dollar-annotated variable names in s with their corresponding
// value or a blank. s MUST be heap-allocated.
bool expand_str(char **envp, char **s);
t_tl *parse(char **envp, char *src);
#endif
