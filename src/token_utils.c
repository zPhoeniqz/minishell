/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whuth <whuth@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 13:39:28 by whuth             #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2026/05/06 17:14:54 by whuth            ###   ########.fr       */
=======
/*   Updated: 2026/03/18 13:47:27 by whuth            ###   ########.fr       */
>>>>>>> 1474c6e4b081d56d1f45c35bc3166decbe0f4df4
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include <stdlib.h>

<<<<<<< HEAD
t_token	*token_init(t_ttype type, char *token, t_token *next_token)
{
	t_token	*out;

	out = malloc(sizeof(t_token));
	if (!out)
		return (NULL);
	out->type = type;
	out->token = ft_strdup(token);
	if (!out->token && token)
		return (free(out), NULL);
	out->next_token = next_token;
	return (out);
}

void	token_destroy(t_token *token)
{
	free(token->token);
	free(token);
}

t_tl	*tl_init(void)
{
	t_tl	*out;

	out = malloc(sizeof(t_tl));
	if (!out)
		return (NULL);
	out->tokens = NULL;
	out->ll = 0;
	return (out);
}

void	tl_destroy(t_tl *tl)
{
	t_token	*cur;
	t_token	*ncur;

	cur = tl->tokens;
	while (cur)
	{
		ncur = cur->next_token;
		token_destroy(cur);
		cur = ncur;
	}
	free(tl);
}

bool	ft_isdelim(char c)
{
	return (ft_isspace(c) || c == '|' || c == '>' || c == '<' || c == '\0');
=======
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

t_tl *tl_init() {
  t_tl *out = malloc(sizeof(t_tl));
  if (!out)
    return NULL;
  out->tokens = NULL;
  out->ll = 0;
  return out;
}

void tl_destroy(t_tl *tl) {
  t_token *cur = tl->tokens;
  while (cur) {
    t_token *ncur = cur->next_token;
    token_destroy(cur);
    cur = ncur;
  }

  free(tl);
}

bool ft_isdelim(char c) {
  return ft_isspace(c) || c == '|' || c == '>' || c == '<' || c == '\0';
>>>>>>> 1474c6e4b081d56d1f45c35bc3166decbe0f4df4
}
