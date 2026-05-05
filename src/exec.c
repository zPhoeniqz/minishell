/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whuth <whuth@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 18:17:18 by whuth             #+#    #+#             */
/*   Updated: 2026/05/04 02:34:19 by whuth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "../inc/path.h"
#include "../inc/signals.h"
#include "../inc/gnl.h"
#include "../libft/libft.h"
#include <fcntl.h>
#include <stdbool.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>

static t_token *build_stage(t_token *cur, t_stage *st) {
  int cap;
  char **tmp;

  ft_bzero(st, sizeof(*st));
  cap = 8;
  st->argv = ft_calloc(cap, sizeof(char *));
  if (!st->argv)
    return (NULL);
  while (cur && cur->type != Pipe) {
    if (cur->type == Argument) {
      if (st->argc + 1 >= cap) {
        cap *= 2;
        tmp = ft_calloc(cap, sizeof(char *));
        if (!tmp)
          return (free(st->argv), st->argv = NULL, NULL);
        ft_memcpy(tmp, st->argv, st->argc * sizeof(char *));
        free(st->argv);
        st->argv = tmp;
      }
      st->argv[st->argc++] = cur->token;
    } else if (cur->type == InFile)
      st->in_file = cur->token;
    else if (cur->type == OutFile) {
      st->out_file = cur->token;
      st->append = false;
    } else if (cur->type == OutFileAppend) {
      st->out_file = cur->token;
      st->append = true;
    } else if (cur->type == Heredoc)
      st->heredoc = cur->token;
    cur = cur->next_token;
  }
  st->argv[st->argc] = NULL;
  if (cur && cur->type == Pipe)
    return (cur->next_token);
  return (NULL);
}

static bool is_builtin(const char *name) {
  static const char *b[] = {"echo",  "cd",  "pwd",  "export",
                            "unset", "env", "exit", NULL};
  int i;

  i = 0;
  while (b[i]) {
    if (ft_strncmp(name, b[i], ft_strlen(b[i]) + 1) == 0)
      return (true);
    i++;
  }
  return (false);
}

static int run_builtin(t_stage *st, char **envp) {
  const char *n;

  n = st->argv[0];
  if (ft_strncmp(n, "echo", 5) == 0)
    return (echo(st->argc, st->argv, envp));
  if (ft_strncmp(n, "cd", 3) == 0)
    return (cd(st->argc, st->argv, envp));
  if (ft_strncmp(n, "pwd", 4) == 0)
    return (pwd(st->argc, st->argv, envp), 0);
  if (ft_strncmp(n, "export", 7) == 0)
    return (export(st->argc, st->argv, envp));
  if (ft_strncmp(n, "unset", 6) == 0)
    return (unset(st->argc, st->argv, envp));
  if (ft_strncmp(n, "env", 4) == 0)
    return (env(st->argc, st->argv, envp), 0);
  if (ft_strncmp(n, "exit", 5) == 0) {
    if (st->argc > 1)
      exit(ft_atoi(st->argv[1]));
    exit(0);
  }
  return (1);
}

static char *resolve_path(const char *name, char **envp) {
  char *path_val;
  char **dirs;
  char *candidate;
  int i;

  if (!name || !*name)
    return (NULL);
  if (ft_strchr(name, '/')) {
    if (access(name, X_OK) == 0)
      return (ft_strdup(name));
    return (NULL);
  }
  path_val = NULL;
  i = 0;
  while (envp[i]) {
    if (ft_strncmp(envp[i], "PATH=", 5) == 0) {
      path_val = envp[i] + 5;
      break;
    }
    i++;
  }
  if (!path_val)
    return (NULL);
  dirs = ft_split(path_val, ':');
  if (!dirs)
    return (NULL);
  i = 0;
  candidate = NULL;
  while (dirs[i]) {
    candidate = pathjoin(dirs[i], name);
    if (candidate && access(candidate, X_OK) == 0)
      break;
    free(candidate);
    candidate = NULL;
    i++;
  }
  arr_destroy((void **)dirs);
  return (candidate);
}

static int apply_input(t_stage *st) {
  int fd;
  int p[2];
  pid_t pid;
  char *line;
  size_t dlen;

  if (st->heredoc) {
    if (pipe(p) == -1)
      return (perror("pipe"), -1);
    pid = fork();
    if (pid == -1)
      return (perror("fork"), -1);
    if (pid == 0) {
      close(p[0]);
      dlen = ft_strlen(st->heredoc);
      while (1) {
        write(STDERR_FILENO, "> ", 2);
        line = get_next_line(STDIN_FILENO);
        if (!line)
          break;
        if (ft_strncmp(line, st->heredoc, dlen) == 0 &&
            (line[dlen] == '\n' || line[dlen] == '\0')) {
          free(line);
          break;
        }
        ft_putstr_fd(line, p[1]);
        free(line);
      }
      close(p[1]);
      exit(0);
    }
    close(p[1]);
    dup2(p[0], STDIN_FILENO);
    close(p[0]);
    waitpid(pid, NULL, 0);
    return (0);
  }
  if (st->in_file) {
    fd = open(st->in_file, O_RDONLY);
    if (fd == -1)
      return (perror(st->in_file), -1);
    dup2(fd, STDIN_FILENO);
    close(fd);
  }
  return (0);
}

static int apply_output(t_stage *st) {
  int fd;
  int flags;

  if (!st->out_file)
    return (0);
  if (st->append)
    flags = O_WRONLY | O_CREAT | O_APPEND;
  else
    flags = O_WRONLY | O_CREAT | O_TRUNC;
  fd = open(st->out_file, flags, 0644);
  if (fd == -1)
    return (perror(st->out_file), -1);
  dup2(fd, STDOUT_FILENO);
  close(fd);
  return (0);
}

static void exec_child(t_stage *st, char **envp) {
  char *path;

  if (apply_input(st) == -1)
    exit(1);
  if (apply_output(st) == -1)
    exit(1);
  if (!st->argv || !st->argv[0])
    exit(0);
  if (is_builtin(st->argv[0]))
    exit(run_builtin(st, envp));
  path = resolve_path(st->argv[0], envp);
  if (!path) {
    ft_putstr_fd(st->argv[0], STDERR_FILENO);
    ft_putstr_fd(": command not found\n", STDERR_FILENO);
    exit(127);
  }
  execve(path, st->argv, envp);
  perror(st->argv[0]);
  free(path);
  exit(126);
}

static int exec_single(t_stage *st, char **envp) {
  pid_t pid;
  int status;
  int sin;
  int sout;
  int ret;

  if (!st->argv || !st->argv[0])
    return (0);
  if (is_builtin(st->argv[0])) {
    sin = dup(STDIN_FILENO);
    sout = dup(STDOUT_FILENO);
    if (apply_input(st) == -1 || apply_output(st) == -1) {
      dup2(sin, STDIN_FILENO);
      dup2(sout, STDOUT_FILENO);
      close(sin);
      close(sout);
      return (1);
    }
    ret = run_builtin(st, envp);
    dup2(sin, STDIN_FILENO);
    dup2(sout, STDOUT_FILENO);
    close(sin);
    close(sout);
    return (ret);
  }
  pid = fork();
  if (pid == -1)
    return (perror("fork"), 1);
  if (pid == 0)
    exec_child(st, envp);
  waitpid(pid, &status, 0);
  if (WIFEXITED(status))
    return (WEXITSTATUS(status));
  if (WIFSIGNALED(status))
    return (128 + WTERMSIG(status));
  return (1);
}

static int exec_pipeline(t_stage *stages, int n, char **envp) {
  pid_t *pids;
  int prev_read;
  int p[2];
  int i;
  int status;
  int ret;

  pids = ft_calloc(n, sizeof(pid_t));
  if (!pids)
    return (perror("calloc"), 1);
  addsighandler(SIGINT, SIG_IGN, 0);
  prev_read = -1;
  i = 0;
  while (i < n) {
    if (i < n - 1 && pipe(p) == -1) {
      free(pids);
      addsighandler(SIGINT, signals_forward_int, 0);
      return (perror("pipe"), 1);
    }
    pids[i] = fork();
    if (pids[i] == -1) {
      free(pids);
      addsighandler(SIGINT, signals_forward_int, 0);
      return (perror("fork"), 1);
    }
    if (pids[i] == 0) {
      if (prev_read != -1) {
        dup2(prev_read, STDIN_FILENO);
        close(prev_read);
      }
      if (i < n - 1) {
        close(p[0]);
        dup2(p[1], STDOUT_FILENO);
        close(p[1]);
      }
      exec_child(&stages[i], envp);
    }
    if (prev_read != -1)
      close(prev_read);
    if (i < n - 1) {
      close(p[1]);
      prev_read = p[0];
    }
    i++;
  }
  ret = 0;
  i = 0;
  while (i < n) {
    waitpid(pids[i], &status, 0);
    if (i == n - 1) {
      if (WIFEXITED(status))
        ret = WEXITSTATUS(status);
      else if (WIFSIGNALED(status))
        ret = 128 + WTERMSIG(status);
    }
    i++;
  }
  free(pids);
  addsighandler(SIGINT, signals_forward_int, 0);
  return (ret);
}

int exec(t_data *data) {
  t_stage *stages;
  int n_stages;
  t_token *cur;
  int i;
  int ret;

  if (!data || !data->tokenlist || !data->tokenlist->tokens)
    return (0);
  n_stages = 1;
  cur = data->tokenlist->tokens;
  while (cur) {
    if (cur->type == Pipe)
      n_stages++;
    cur = cur->next_token;
  }
  stages = ft_calloc(n_stages, sizeof(t_stage));
  if (!stages)
    return (perror("calloc"), 1);
  cur = data->tokenlist->tokens;
  i = 0;
  while (i < n_stages) {
    cur = build_stage(cur, &stages[i]);
    if (!stages[i].argv) {
      while (--i >= 0)
        free(stages[i].argv);
      free(stages);
      return (1);
    }
    i++;
  }
  if (n_stages == 1)
    ret = exec_single(&stages[0], data->envp);
  else
    ret = exec_pipeline(stages, n_stages, data->envp);
  i = 0;
  while (i < n_stages)
    free(stages[i++].argv);
  free(stages);
  return (ret);
}
