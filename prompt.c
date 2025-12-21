#include "libft/libft.h"
#include <linux/limits.h>
#include <stdio.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <stdbool.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

typedef enum e_cwdaction { READ, UPDATE, FREE } t_cwdaction;

const char *cwd_state(t_cwdaction action) {
  static char *cwd = NULL;

  if (action == UPDATE || (action == READ && !cwd)) {
    free(cwd);
    cwd = getcwd(NULL, 0);
  }

  if (action == FREE) {
    free(cwd);
    cwd = NULL;
  }

  return cwd;
}

bool cwd_change(const char *path) {
  if (chdir(path) == -1)
    return false;
  cwd_state(UPDATE);
  return true;
}

static char *prompt_create(const char *path) { return ft_strjoin(path, "> "); }

static void arr_destroy(void **arr) {
  if (!arr)
    return;
  char **oarr = (char **)arr;
  while (*arr)
    free(*arr++);
  free(oarr);
}

char *pathjoin(const char *s1, const char *s2) {
  size_t l1 = ft_strlen(s1);
  if (l1 <= 1)
    return NULL;
  bool separator_exists = s1[l1 - 1] == '/' || s2[0] == '/';
  size_t len = l1 + !separator_exists + ft_strlen(s2) + 1;
  char *out = malloc(len);
  if (!out)
    return NULL;

  ft_strlcpy(out, s1, len);
  if (!separator_exists)
    out[l1] = '/';
  ft_strlcat(out, s2, len);
  return out;
}

bool run_system_exec(char **argv, char **envp) {
  pid_t pid;
  int status;
  char *cur_file_path;
  char **path;

  pid = fork();
  if (pid > 0) {
    waitpid(pid, &status, 0);
    return true;
  }

  path = ft_split(getenv("PATH"), ':');
  char **opath = path;

  while (path) {
    cur_file_path = pathjoin(*path, argv[0]);
    if (!cur_file_path)
      return false;

    execve(cur_file_path, argv, envp);
    free(cur_file_path);
    path++;
  }

  arr_destroy((void **)opath);
  return false;
}

// TODO error handling of readline, ft_split, etc.
// TODO handle executables that are in PATH
void prompt_run(char **envp) {
  char *prompt = prompt_create(cwd_state(READ));
  char *input = NULL;
  char **argv = NULL;
  pid_t pid;
  int status;
  while (true) {
    if (ft_strncmp(cwd_state(READ), prompt, ft_strlen(prompt) - 2) != 0) {
      free(prompt);
      prompt = prompt_create(cwd_state(READ));
    }

    input = readline(prompt);
    if (ft_strlen(input) < 1)
      continue;
    argv = ft_split(input, ' ');
    add_history(input);
    free(input);
    if (!ft_strchr(argv[0], '/')) {
      if (!run_system_exec(argv, envp))
        return;
      continue;
    }

    pid = fork();
    if (pid == 0) {
      execve(argv[0], argv, envp);
    } else {
      waitpid(pid, &status, 0);
    }
    arr_destroy((void **)argv);
  }
}

int main(int argc, char **argv, char **envp) {
  (void)argc;
  (void)argv;
  prompt_run(envp);
}
