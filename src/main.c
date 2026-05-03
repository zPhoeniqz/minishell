/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whuth <whuth@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/26 17:48:36 by whuth             #+#    #+#             */
/*   Updated: 2026/04/26 18:02:21 by whuth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include <stdlib.h>

extern char **environ;

int main(int argc, char **argv) {
  char *prompt;
  char *input;
  pid_t pid;
  int status;
  t_data data;

  prompt = NULL;
  input = NULL;
  data.envp = dup_env(environ);
  if (!data.envp)
    return EXIT_FAILURE;
  prompt_create(&prompt, cwd_state(UPDATE));
  int exit_code = 0;
  while (true) {
    addsighandler(SIGINT, signals_forward_int, 0);
    if (ft_strncmp(cwd_state(READ), prompt, ft_strlen(prompt) - 2) != 0)
      prompt_create(&prompt, cwd_state(READ));
    status = readstring(&input, prompt);
    if (status == 0)
      continue;
    else if (status == -1)
      return (cwd_state(FREE), free(prompt));

    data.tokenlist = get_tokens(data.envp, input);
    if (!data.tokenlist)
      ...;
    exit_code = exec(data);
    arr_destroy((void **)argv);
  }
  arr_destroy((void **)data.envp);
}
