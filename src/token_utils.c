/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whuth <whuth@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 13:39:28 by whuth             #+#    #+#             */
/*   Updated: 2026/05/06 17:38:44 by whuth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include <stdlib.h>

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
}
