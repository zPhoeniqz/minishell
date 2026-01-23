/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whuth <whuth@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 16:36:28 by whuth             #+#    #+#             */
/*   Updated: 2026/01/23 12:02:38 by whuth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static char	*skip_separators(char *in)
{
	while (del_occ(*in))
		in++;
	return (in);
}

static char	**strarr_destruct(char **in, int n)
{
	while (n >= 0)
		free(in[n--]);
	free(in);
	return (NULL);
}

static char	*alloc_token(const char *input, size_t *elen)
{
	*elen = token_len(input);
	return ((char *)ft_calloc(*elen + (*elen > 0), 1));
}

char	**gettokens(char *input)
{
	int		elcount;
	char	**out;
	int		i;
	size_t	elen;

	elcount = (int)count_elts(input);
	out = ft_calloc(elcount + 1, sizeof(char *));
	if (!out)
		return (NULL);
	i = 0;
	while (i < elcount)
	{
		input = skip_separators(input);
		out[i] = alloc_token(input, &elen);
		if (!out[i])
			return (strarr_destruct(out, i));
		if (!check_quote(input, &elen))
			return (strarr_destruct(out, i + 1));
		ft_strlcpy(out[i], input, elen + 1);
		input += elen;
		++i;
	}
	out[i] = NULL;
	return (out);
}

//*/
int	main(void)
{
	int		i;
	char	*input;
	char	**tokens;

	input = "ls 3123  \'  \"a a sd \" a \'asdsdasd -a \n | cat\t  $VAR";
	tokens = gettokens(input);
	i = 0;
	while (tokens[i])
		ft_printf("%s\n", tokens[i++]);
	i = 0;
	while (tokens[i])
		free(tokens[i++]);
	free(tokens);
}
//*/
