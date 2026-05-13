/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbindl <pbindl@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/21 12:51:02 by pbindl            #+#    #+#             */
/*   Updated: 2026/05/11 20:04:18 by pbindl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "../inc/utils.h"
#include "../libft/libft.h"
#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

static bool	parser_init(char **src, char ***cursor, t_tl **out)
{
	if (!src)
		return (false);
	*cursor = src;
	*out = tl_init();
	if (!out)
		return (false);
	return (true);
}

static bool	tjoin(t_token *cur_token, t_token *ntoken)
{
	char	*newtoken;

	if (!ntoken)
		return (false);
	newtoken = ft_strjoin(cur_token->token, ntoken->token);
	if (!newtoken)
		return (false);
	free(cur_token->token);
	token_destroy(ntoken);
	cur_token->token = newtoken;
	return (true);
}

t_tl	*parse(char **envp, char *src, int last_exit_code)
{
	char	**cursor;
	t_tl	*out;
	t_token	*cur_token;

	if (!parser_init(&src, &cursor, &out))
		return (NULL);
	out->tokens = get_next_token(envp, cursor, last_exit_code);
	cur_token = out->tokens;
	while (cur_token)
	{
		if (errno == EMORETOREAD)
		{
			if (!tjoin(cur_token, get_next_token(envp, cursor, last_exit_code)))
				return (tl_destroy(out), NULL);
			continue ;
		}
		out->ll++;
		cur_token->next_token = get_next_token(envp, cursor, last_exit_code);
		if (!cur_token->next_token && cur_token->type == Pipe)
			return (syntaxerr('|'), tl_destroy(out), NULL);
		cur_token = cur_token->next_token;
		if (errno != 0 && errno != EMORETOREAD)
			return (tl_destroy(out), NULL);
	}
	return (out);
}

/*
int	main(int argc, char **argv, char **envp) {
  if (argc != 2)
	return (1);

  t_tl *tokens = parse(envp, argv[1], 0);
  if (!tokens)
	return (1);

  t_token *cur_token = tokens->tokens;
  for (int i = 0; i < tokens->ll; i++) {

	printf("== Token %p ==\n", cur_token);
	printf("Type: %c\n", cur_token->type);
	printf("Content: `%s`\n", cur_token->token);
	printf("Next Token: %p\n\n", cur_token->next_token);

	t_token *next_token = cur_token->next_token;
	token_destroy(cur_token);
	cur_token = next_token;
  }
  free(tokens);
}
//*/
