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
#include "../inc/path.h"
#include "../inc/prompt.h"
#include "../inc/signals.h"
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

extern char **environ;

int main() {
  char *prompt;
  char *input;
  int status;
  t_data data;

  prompt = NULL;
  input = NULL;
  data.envp = dup_env(environ);
  prompt_create(&prompt, cwd_state(UPDATE));
  int exit_code = 0;
  while (true) {
    addsighandler(SIGINT, signals_forward_int, 0);
    if (ft_strlen(prompt) != ft_strlen(cwd_state(READ)) - 2 ||
        ft_strncmp(cwd_state(READ), prompt, ft_strlen(prompt) - 2) != 0)
      prompt_create(&prompt, cwd_state(READ));
    status = read_cmd(&input, prompt);
    if (status == 0)
      continue;
    else if (status == -1)
      break;

    data.tokenlist = parse(data.envp, input, exit_code);
    if (errno != 0)
      exit_code = 2;
    if (data.tokenlist) {
      if (errno == 0)
        exit_code = exec(&data);
      tl_destroy(data.tokenlist);
    }
  }
  cwd_state(FREE);
  arr_destroy((void **)data.envp);
}
