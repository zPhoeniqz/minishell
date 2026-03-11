/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whuth <whuth@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 16:36:28 by whuth             #+#    #+#             */
/*   Updated: 2026/01/28 10:05:31 by whuth            ###   ########.fr       */
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

static int	store_token(char **out, int i, char **input, t_vl *vl)
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
	if (out[i][0] == '$')
		out[i] = find_val(out[i] + 1, &vl);
	*input += elen;
	return (1);
}

void	gettokens(char *input, t_data *data)
{
	int		i;
	char	**out;
	int		elcount;

	elcount = (int)count_elts(input);
	out = ft_calloc(elcount + 1, sizeof(char *));
	if (!out)
		return ;
	i = 0;
	while (i < elcount)
	{
		if (!store_token(out, i, &input, data->vl))
			return ;
		i++;
	}
	out[i] = NULL;
	data->tl->tokens = out;
	data->tl->ll = elcount;
}
