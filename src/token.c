/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whuth <whuth@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 16:36:28 by whuth             #+#    #+#             */
/*   Updated: 2026/03/24 18:16:41 by whuth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

extern char	**environ;

static char	*skip_separators(char *in)
{
	if (*in >= 33 && *in <= 126 && !is_paren(*in))
		return (in);
	while (*in && is_del(*in) && !is_paren(*in))
		++in;
	return (in);
}

//*
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
//*/

static void sub_val(char **out, size_t elen, int index)
{
	int		cmp;
	int		val_len;
	char	*tmp_key;

	tmp_key = ft_calloc(sizeof(char), elen + 1);
	if (!tmp_key)
		return ;
	ft_strlcpy(tmp_key, out[index] + 1, elen);
	printf("tmpkey\t\"%s\"\n", tmp_key);
	while (*environ)
	{
		cmp = ft_strncmp(*environ, tmp_key, elen - 1);
		if (cmp == 0)
		{
			printf("found matching key\n");
			val_len = ft_strlen(*environ) - elen + 1;
			free(out[index]);
			out[index] = ft_calloc(val_len, sizeof(char));
			if (!out)
				return (free(tmp_key));
			printf("lenval\t%d\n", val_len);
			ft_strlcpy(out[index], *environ + elen, val_len);
			printf("new val\t%s\n", out[index]);
			return (free(tmp_key));
		}
		++environ;
	}
	printf("no matching key\n");
	free(out[index]);
	out[index] = ft_calloc(1, 1);
	return (free(tmp_key));
}

static int	store_token(char **out, int *i, char **input)
{
	size_t	elen;

	*input = skip_separators(*input);
	printf("in\t\"%s\"\n", *input);
	elen = next_elen(*input, out, *i);
	printf("elen\t%zu\n", elen);
	if (elen == 0)
		return (0);
	out[*i] = ft_calloc(sizeof(char), elen + 1);
	if (!out[*i])
	{
		strarr_destruct(out, *i - 1);
		return (0);
	}
	ft_strlcpy(out[*i], *input, elen + 1);
	if (out[*i][0] == '$' && out[*i][1] && !is_del(out[*i][1]))
		sub_val(out, elen, *i);
	*input += elen;
	printf("\n");
	return (1);
}

void	gettokens(char *input, t_data *data)
{
	int		i;
	char	**out;
	int		elcount;

	elcount = (int)count_tokens(input);
	out = ft_calloc(elcount + 1, sizeof(char *));
	if (!out)
		return ;
	i = 0;
	printf("elc\t%d\n\n", elcount);
	while (i < elcount)
	{
		if (!store_token(out, &i, &input))
			return ;
		++i;
	}
	out[i] = NULL;
	data->tl->tokens = out;
	data->tl->ll = elcount;
}
