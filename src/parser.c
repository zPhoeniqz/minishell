/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbindl <pbindl@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/21 12:51:02 by pbindl            #+#    #+#             */
/*   Updated: 2026/04/21 22:53:32 by pbindl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "../inc/utils.h"
#include "../libft/libft.h"
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>

// replaces the dollar-annotated variable names in s with their corresponding
// value or a blank. s MUST be heap-allocated.
bool expand_str(char **envp, char **s, int last_exit_code) {
  char *value;
  bool squoted = false;
  char *out = NULL;
  if (!*s)
    return (false);
  int i = 0;
  while ((*s)[i]) {
    if ((*s)[i] == '\'')
      squoted = !squoted;
    if (!squoted && (*s)[i] == '$') {
      int end = i + 1;
      if ((*s)[end] != '?') {
        while (!ft_isdelim((*s)[end]))
          end++;
        char c = (*s)[end];
        (*s)[end] = 0;
        value = ft_getenv(envp, *s + i + 1);
        if (!value)
          value = " ";
        (*s)[end] = c;
      } else {
        value = ft_itoa(last_exit_code);
        end++;
      }
      size_t nsize = i + ft_strlen(value) + ft_strlen(*s + end) + 1;
      out = ft_calloc(nsize, 1);
      if (!out)
        return (free(*s), false);
      ft_memcpy(out, *s, i);
      ft_strlcat(out, value, nsize);
      ft_strlcat(out, *s + end, nsize);
      free(*s);
      *s = out;
    }
    i++;
  }

  return true;
}

static void syntaxerr(char invalid) {
  ft_putstr_fd("Syntax error near '", STDERR_FILENO);
  ft_putchar_fd(invalid, STDERR_FILENO);
  ft_putendl_fd("'", STDERR_FILENO);
  errno = EINVAL;
}

static t_ttype determine_ttype(char **cursor) {
  char *cur = *cursor;
  t_ttype out = Argument;
  if (cur[0] == '<' && cur[1] == '<') {
    out = Heredoc;
    cur++;
  } else if (cur[0] == '<')
    out = InFile;
  else if (cur[0] == '>' && cur[1] == '>') {
    out = OutFileAppend;
    cur++;
  } else if (cur[0] == '>')
    out = OutFile;
  else if (cur[0] == '|')
    out = Pipe;
  cur += out != Argument;
  *cursor = cur;
  return out;
}

static t_token *get_next_token(char **envp, char **cursor, int last_exit_code) {
  while (ft_isspace(**cursor))
    (*cursor)++;
  if (!**cursor)
    return NULL;
  t_ttype type = determine_ttype(cursor);
  if (type == Pipe)
    return token_init(Pipe, "|", NULL);
  char *cur = *cursor;
  while (ft_isspace(*cur))
    cur++;
  bool dquoted = *cur == '"';
  bool squoted = *cur == '\'';

  cur += squoted || dquoted;

  int i = 0;
  while (cur[i]) {
    if (ft_isdelim(cur[i]) && !dquoted && !squoted)
      break;
    if (cur[i] == '"' && !squoted) {
      dquoted = false;
      break;
    }
    if (cur[i] == '\'' && !dquoted) {
      squoted = false;
      break;
    }
    i++;
  }

  if (squoted || dquoted || i == 0)
    return (syntaxerr('"' * dquoted + '\'' * squoted +
                      '>' * (type == OutFile || type == OutFileAppend) +
                      '<' * (type == InFile || type == Heredoc)),
            NULL);

  char c = cur[i];
  cur[i] = 0;
  t_token *out = token_init(type, cur, NULL);
  if (out->type != Heredoc && !expand_str(envp, &out->token, last_exit_code))
    return (free(out), NULL);
  cur[i] = c;
  *cursor = cur + i + (cur[i] == '"' || cur[i] == '\'');
  errno = 0;
  return out;
}

t_tl *parse(char **envp, char *src, int last_exit_code) {
  if (!src)
    return NULL;
  char **cursor = &src;
  t_tl *out = tl_init();
  if (!out)
    return NULL;
  out->tokens = get_next_token(envp, cursor, last_exit_code);
  t_token *cur_token = out->tokens;
  bool cur_is_pipe = false;
  while (cur_token) {
    cur_is_pipe = cur_token->type == Pipe;
    out->ll++;
    cur_token->next_token = get_next_token(envp, cursor, last_exit_code);
    cur_token = cur_token->next_token;
    if (errno != 0)
      return (tl_destroy(out), NULL);
  }

  if (cur_is_pipe) {
    syntaxerr('|');
    return (tl_destroy(out), NULL);
  }

  return out;
}

/*/
int main(int argc, char **argv, char **envp) {
  if (argc != 2)
    return 1;

  t_tl *tokens = get_tokens(envp, argv[1]);
  if (!tokens)
    return 1;

  t_token *cur_token = tokens->tokens;
  for (int i = 0; i < tokens->ll; i++) {

    printf("== Token %p ==\n", cur_token);
    printf("Type: %c\n", cur_token->type);
    printf("Content: `%s`\n", cur_token->token);
    printf("Next Token: %p\n\n", cur_token->next_token);

    t_token *next_token = cur_token->next_token;
    token_destroy(cur_token);
    cur_token = next_token;
  }
  free(tokens);
}
//*/
