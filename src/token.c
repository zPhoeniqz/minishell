/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whuth <whuth@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 16:36:28 by whuth             #+#    #+#             */
/*   Updated: 2026/03/18 13:47:23 by whuth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static char	*skip_separators(char *in)
{
	while (*in && is_del(*in) && !is_paren(*in))
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

static int	check_for_var(char *input, int *var_loc)
{
	int	i;

	i = 0;
	while (!is_del(*(input + i)) && *(input + i))
	{
		if (*(input + i) == '$')
		{
			*var_loc = i;
			return (1);
		}
		++i;
	}
	*var_loc = 0;
	return (0);
}

static int	store_token(char **out, int *i, char **input, t_vl *vl)
{
	size_t	elen;
	int		var_loc;

	*input = skip_separators(*input);
	elen = next_elen(*input, out, *i);
	if (elen == 0)
		return (0);
	if (check_for_var(*input, &var_loc))
	{
		out[*i] = ft_calloc(var_loc + 1, 1);
		if (!out[*i])
		{
			strarr_destruct(out, *i - 1);
			return (0);
		}
		ft_strlcpy(out[*i], *input, var_loc + 1);
		out[++(*i)] = ft_calloc(elen - var_loc, 1);
		if (!out[*i])
		{
			strarr_destruct(out, *i - 1);
			return (0);
		}
		ft_strlcpy(out[*i], *input + elen - var_loc - 1, elen - var_loc + 1);
	}
	else
	{
		out[*i] = ft_calloc(elen + 1, 1);
		if (!out[*i])
		{
			strarr_destruct(out, *i - 1);
			return (0);
		}
		ft_strlcpy(out[*i], *input, elen + 1);
	}
	if (out[*i][0] == '$' && out[*i][1] && !is_del(out[*i][1]))
		out[*i] = find_val(out[*i] + 1, &vl);
	*input += elen;
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
	while (i < elcount)
	{
		if (!store_token(out, &i, &input, data->vl))
			return ;
		i++;
	}
	out[i] = NULL;
	data->tl->tokens = out;
	data->tl->ll = elcount;
}
