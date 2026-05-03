/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whuth <whuth@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 13:39:28 by whuth             #+#    #+#             */
/*   Updated: 2026/03/18 13:47:27 by whuth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_token *token_init(t_ttype type, char *token, t_token *next_token) {
  t_token *out = malloc(sizeof(t_token));
  if (!out)
    return NULL;
  out->type = type;
  out->token = ft_strdup(token);
  if (!out->token && token)
    return (free(out), NULL);
  out->next_token = next_token;
  return out;
}

void token_destroy(t_token *token) {
  free(token->token);
  free(token);
}

bool ft_isdelim(char c) {
  return ft_isspace(c) || c == '|' || c == '>' || c == '<' || c == '\0';
}
