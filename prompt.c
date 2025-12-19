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

// TODO error handling of readline, ft_split, etc.
// TODO handle executables that are in PATH
void prompt_run() {
  char *prompt = prompt_create(cwd_state(READ));
  char *input = NULL;
  char **argv = NULL;
  pid_t pid;
  int status;
  char *full_path;
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
    if (ft_strnstr(argv[0], "/", ft_strlen(argv[0])))
      full_path = argv[0];
    else
      continue;

    pid = fork();
    if (pid == 0) {
      execve(full_path, argv, NULL);
    } else {
      waitpid(pid, &status, 0);
    }
    arr_destroy((void **)argv);
  }
}
