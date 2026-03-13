/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whuth <whuth@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 16:36:28 by whuth             #+#    #+#             */
/*   Updated: 2026/01/23 15:37:01 by whuth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static char	*skip_separators(char *in)
{
	while (*in && del_occ(*in) && !is_paren(*in))
		in++;
	return (in);
}

static size_t	next_elen(char *input, char **out, int i)
{
	size_t	elen;

	elen = 0;
	if (!check_quote(input, &elen))
	{
		strarr_destruct(out, i - 1);
		return (0);
	}
	if (elen == 0)
	{
		if (is_paren(*input))
			elen = 1;
		else
			elen = token_len(input);
	}
	return (elen);
}

static int	store_token(char **out, int i, char **input)
{
	size_t	elen;

	*input = skip_separators(*input);
	elen = next_elen(*input, out, i);
	if (elen == 0)
		return (0);
	out[i] = ft_calloc(elen + 1, 1);
	if (!out[i])
	{
		strarr_destruct(out, i - 1);
		return (0);
	}
	ft_strlcpy(out[i], *input, elen + 1);
	*input += elen;
	return (1);
}

char	**gettokens(char *input)
{
	int		i;
	char	**out;
	int		elcount;

	elcount = (int)count_elts(input);
	out = ft_calloc(elcount + 1, sizeof(char *));
	if (!out)
		return (NULL);
	i = 0;
	while (i < elcount)
	{
		if (!store_token(out, i, &input))
			return (NULL);
		i++;
	}
	out[i] = NULL;
	return (out);
}
//*/
static void	free_tokens(char **tokens)
{
	int	i;

	if (!tokens)
		return ;
	i = 0;
	while (tokens[i])
	{
		free(tokens[i]);
		i++;
	}
	free(tokens);
}

int	main(int ac, char **av)
{
	char	**tokens;
	int		i;

	if (ac != 2)
	{
		ft_putendl_fd("usage: ./tokenizer \"input\"", STDERR_FILENO);
		return (2);
	}
	tokens = gettokens(av[1]);
	if (!tokens)
	{
		ft_putendl_fd("tokenizer error", STDERR_FILENO);
		return (3);
	}
	i = 0;
	while (tokens[i])
	{
		ft_putendl_fd(tokens[i], STDOUT_FILENO);
		i++;
	}
	free_tokens(tokens);
	return (0);
}//*/
