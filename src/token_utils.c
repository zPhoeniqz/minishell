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

static void	update_quotes(char c, unsigned int *dquote, unsigned int *squote)
{
	if (c == '"' && !(*squote))
		*dquote = !(*dquote);
	else if (c == '\'' && !(*dquote))
		*squote = !(*squote);
}
static void	step_count(const char **s, unsigned int *sw,
		unsigned int *tokencount, unsigned int in_quote)
{
	if (!in_quote && is_paren(**s))
	{
		(*tokencount)++;
		*sw = 0;
		(*s)++;
		return ;
	}
	if (!in_quote && is_sep(**s))
	{
		*sw = 0;
		(*s)++;
		return ;
	}
	if (!in_quote && **s == '$')
	{
		(*tokencount)++;
		*sw = 1;
		(*s)++;
		while (**s && !is_sep(**s) && !is_paren(**s) && **s != '$')
			(*s)++;
		*sw = 0;
		return ;
	}
	if (!(*sw))
	{
		*sw = 1;
		(*tokencount)++;
	}
	(*s)++;
}

unsigned int	count_tokens(const char *s)
{
	unsigned int	sw;
	unsigned int	dquote;
	unsigned int	squote;
	unsigned int	tokencount;

	sw = 0;
	dquote = 0;
	squote = 0;
	tokencount = 0;
	while (*s)
	{
		update_quotes(*s, &dquote, &squote);
		step_count(&s, &sw, &tokencount, (dquote || squote));
	}
	ft_printf("%d\n", tokencount);
	return (tokencount);
}

int	check_quote(char *s, size_t *elen)
{
	int		i;
	char	c;

	i = 0;
	if (s[i] == '\"' || s[i] == '\'')
	{
		c = s[i];
		while (s[++i])
		{
			if (s[i] == c)
			{
				*elen = i + 1;
				return (1);
			}
		}
		return (0);
	}
	return (1);
}

size_t	token_len(const char *s)
{
	size_t			i;
	unsigned int	dquote;
	unsigned int	squote;

	if (!s || !*s)
		return (0);
	if (is_paren(*s))
		return (1);
	i = 0;
	dquote = 0;
	squote = 0;
	while (s[i])
	{
		if (s[i] == '"' && !squote)
			dquote = !dquote;
		else if (s[i] == '\'' && !dquote)
			squote = !squote;
		if (!dquote && !squote)
		{
			if (is_sep(s[i]) || is_paren(s[i]))
				break ;
		}
		i++;
	}
	return (i);
}
