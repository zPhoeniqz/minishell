/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbindl <pbindl@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 18:13:45 by pbindl            #+#    #+#             */
/*   Updated: 2026/05/06 19:57:07 by whuth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/path.h"
#include "../inc/minishell.h"
#include "../inc/utils.h"
#include "../libft/libft.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void env(int ac, char **av, char **envp) {
  char **e;

  (void)ac;
  (void)av;
  e = envp;
  while (*e) {
    if (ft_strchr(*e, '='))
      printf("%s\n", *e);
    e++;
  }
}

static int find_var(char **envp, char *varname) {
  size_t len;
  int i;

  if (!varname)
    return (-2);
  len = ft_strlen(varname);
  i = 0;
  while (envp[i]) {
    if (ft_strncmp(envp[i], varname, len) == 0)
      return (i);
    i++;
  }
  return (-1);
}

static bool check_varname(const char *name) {
  if (!ft_isalpha(*name) && *name != '_')
    return (false);
  while (*name) {
    if (!ft_isalnum(*name) && *name != '_')
      return (false);
    name++;
  }
  return (true);
}

static char **var_split(char *s) {
  size_t namelen;
  char **out = ft_calloc(3, sizeof(char *));
  if (!out)
    return NULL;

  char *eqs = ft_strchr(s, '=');
  if (eqs)
    namelen = eqs - s;
  else
    namelen = ft_strlen(s);

  out[0] = ft_calloc(namelen + 1, 1);
  if (!out[0])
    return (free(out), NULL);
  ft_memcpy(out[0], s, namelen);

  if (eqs && eqs[1])
    out[1] = ft_strdup(eqs + 1);
  else if (eqs && !eqs[1])
    out[1] = ft_strdup("");
  else
    out[1] = NULL;

  if (eqs && !out[1])
    return (arr_destroy((void **)out), NULL);

  return out;
}

static void print_exports(char **envp) {
  size_t count = 0;
  bool *printed;
  size_t i;
  size_t j;
  int min_idx;

  while (envp[count])
    count++;

  printed = ft_calloc(count, sizeof(bool));
  if (!printed)
    return;

  i = 0;
  while (i < count) {
    min_idx = -1;
    j = 0;
    while (j < count) {
      if (!printed[j] &&
          (min_idx == -1 ||
           strncmp(envp[j], envp[min_idx], ft_strlen(envp[min_idx])) < 0))
        min_idx = j;
      j++;
    }
    i++;
    if (min_idx == -1)
      continue;
    ft_putstr_fd("declare -x ", STDOUT_FILENO);
    j = 0;
    while (envp[min_idx][j] && envp[min_idx][j] != '=')
      ft_putchar_fd(envp[min_idx][j++], STDOUT_FILENO);

    printed[min_idx] = true;

    if (!envp[min_idx][j]) {
      ft_putchar_fd('\n', STDOUT_FILENO);
      continue;
    }

    ft_putchar_fd(envp[min_idx][j++], STDOUT_FILENO);
    ft_putchar_fd('"', STDOUT_FILENO);
    while (envp[min_idx][j])
      ft_putchar_fd(envp[min_idx][j++], STDOUT_FILENO);
    ft_putendl_fd("\"", STDOUT_FILENO);
  }

  free(printed);
}

int export(int ac, char **av, char ***envp) {
  char **var;
  int failures;

  if (ac <= 1)
    return (print_exports(*envp), 0);

  failures = 0;
  av++;
  while (ac > 1) {
    var = var_split(*av);
    if (var && check_varname(*var)) {
      failures += ft_setenv(envp, var[0], var[1], true);
    } else {
      failures += 1;
      if (var) {
        ft_putstr_fd("export: not an identifier: ", STDERR_FILENO);
        ft_putendl_fd(*var, STDERR_FILENO);
      }
    }
    if (var)
      arr_destroy((void **)var);
    ac--;
    av++;
  }
  return (failures != 0);
}

void pwd(int ac, char **av, char **envp) {
  (void)ac;
  (void)av;
  (void)envp;
  printf("%s\n", cwd_state(READ));
}

static void unset_single(char **envp, char *envname) {
  int idx;
  int num_vars;
  int i;

  idx = find_var(envp, envname);
  if (idx < 0)
    return;
  num_vars = 0;
  while (envp[num_vars])
    num_vars++;
  free(envp[idx]);
  i = idx;
  while (i < num_vars - 2) {
    envp[i] = envp[i + 1];
    i++;
  }
  envp[num_vars - 2] = 0;
}

int unset(int ac, char **av, char ***envp) {
  int i;

  i = 1;
  while (i < ac)
    unset_single(*envp, av[i++]);
  return (0);
}

int echo(int ac, char **av, char **envp) {
  int i;
  bool nl;
  char *s;

  (void)envp;
  if (ac <= 1) {
    printf("\n");
    return (0);
  }
  nl = true;
  i = 1;
  while (i < ac && ft_strncmp(av[i], "-n", 2) == 0) {
    s = ft_strrchr(av[i], 'n');
    if (!s || !ft_isdelim(s[1]))
      break;
    nl = false;
    i++;
  }
  while (i < ac - 1)
    printf("%s ", av[i++]);
  if (i < ac)
    printf("%s", av[i]);
  if (nl)
    printf("\n");
  return (0);
}

int cd(int ac, char **av, char **envp) {
  if (ac != 2)
    return (0);
  if (chdir(av[1]) < 0) {
    perror("cd");
    return (1);
  }
  ft_setenv(&envp, "PWD", av[1], true);
  cwd_state(UPDATE);
  return (0);
}
