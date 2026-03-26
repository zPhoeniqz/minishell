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

static char	*sub_val(char *s, t_vl **vl, size_t elen)
{
	int		cmp;
	int		val_len;
	char	*tmp_key;
	char	*out_val;

	tmp_key = calloc(sizeof(char), elen + 1);
	if (!tmp_key)
		return (NULL);
	ft_strlcpy(tmp_key, s, elen);
	printf("tmpkey\t\"%s\"\n", tmp_key);
	while (*vl)
	{
		cmp = ft_strncmp((*vl)->key, tmp_key, elen);
		if (cmp == 0)
		{
			val_len = ft_strlen((*vl)->value);
			out_val = calloc(sizeof(char), val_len + 1);
			if (!out_val)
				return (free(tmp_key), NULL);
			ft_strlcpy(out_val, (*vl)->value, val_len + 1);
			printf("key_val\t\"%s\"\n", out_val);
			return (free(tmp_key), out_val);
		}
		*vl = (*vl)->next;
	}
	return (free(tmp_key), NULL);
}

static char	*skip_separators(char *in)
{
	if (*in >= 33 && *in <= 126 && !is_paren(*in))
		return (in);
	while (*in && is_del(*in) && !is_paren(*in))
		++in;
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

static int	store_token(char **out, int *i, char **input, t_vl *vl)
{
	char	*tmp;
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
	{
		tmp = out[*i];
		free(out[*i]);
		out[*i] = sub_val(tmp + 1, &vl, elen);
	}
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
		if (!store_token(out, &i, &input, data->vl))
			return ;
		++i;
	}
	out[i] = NULL;
	data->tl->tokens = out;
	data->tl->ll = elcount;
}
