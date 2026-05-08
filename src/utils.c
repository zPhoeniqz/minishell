/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whuth <whuth@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 16:51:36 by whuth             #+#    #+#             */
/*   Updated: 2026/04/15 15:11:41 by pbindl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

void *ft_realloc(void *ptr, size_t newsize) {
  void *out;

  if (!ptr)
    return (malloc(newsize));
  if (ptr && newsize == 0)
    return (ptr);
  out = malloc(newsize);
  if (!out)
    return (NULL);
  ft_memmove(out, ptr, newsize);
  return (out);
}

void arr_destroy(void **arr) {
  char **oarr;

  if (!arr)
    return;
  oarr = (char **)arr;
  while (*arr)
    free(*arr++);
  free(oarr);
}

char **dup_env(char **envp) {
  size_t n = 0;
  while (envp[n])
    n++;
  char **out = ft_calloc(n + 1, sizeof(char *));
  if (!out)
    return NULL;

  n = 0;
  while (envp[n]) {
    out[n] = ft_strdup(envp[n]);
    if (!out[n])
      return (arr_destroy((void **)out), NULL);
    n++;
  }

  return out;
}

int find_env(const char **envp, const char *name) {
  size_t lname;
  int out;

  lname = ft_strlen(name);
  out = 0;
  while (envp[out]) {
    if (ft_strncmp(name, envp[out], lname) == 0)
      return (out);
    out++;
  }
  return (-1);
}

static char *make_envstr(const char *name, const char *value) {
  char *envstr;
  size_t len;

  len = ft_strlen(name) + 2;
  if (value)
    len += ft_strlen(value);

  envstr = ft_calloc(len, 1);
  if (!envstr)
    return (NULL);
  memcpy(envstr, name, ft_strlen(name));
  envstr[ft_strlen(name)] = '=';
  if (value)
    memcpy(envstr + ft_strlen(name) + 1, value, ft_strlen(value));
  else
    envstr[ft_strlen(name)] = 0;
  return (envstr);
}

int ft_setenv(char ***envp, const char *name, const char *value, bool rewrite) {
  int idx;
  char *envstr;
  char **newenv;

  idx = find_env((const char **)(*envp), name);
  if (idx != -1 && !rewrite)
    return (0);

  envstr = make_envstr(name, value);
  if (!envstr)
    return 1;
  if (idx != -1) {
    free((*envp)[idx]);
    (*envp)[idx] = envstr;
    return 0;
  }

  idx = 0;
  while ((*envp)[idx])
    idx++;

  newenv = ft_calloc(idx + 2, sizeof(char *));
  if (!newenv)
    return (free(envstr), 1);
  ft_memcpy(newenv, *envp, idx * sizeof(char *));
  newenv[idx] = envstr;
  free(*envp);
  *envp = newenv;
  return 0;
}

char *ft_getenv(char **envp, const char *name) {
  size_t len = ft_strlen(name);
  char *eqs;

  while (*envp) {
    if (ft_strncmp(*envp, name, len) == 0) {
      eqs = ft_strchr(*envp, '=');
      if (!eqs)
        return NULL;
      return eqs + 1;
    }
    envp++;
  }

  return NULL;
}

bool ft_isspace(char c) {
  return c == ' ' || c == '\f' || c == '\n' || c == '\r' || c == '\t' ||
         c == '\v';
}
