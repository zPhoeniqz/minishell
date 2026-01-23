/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whuth <whuth@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 13:39:28 by whuth             #+#    #+#             */
/*   Updated: 2026/01/23 12:02:50 by whuth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*del_strchr(char *s)
{
	while (*s)
	{
		if (del_occ(*s))
			return (s);
		++s;
	}
	return (NULL);
}

unsigned int	count_elts(const char *s)
{
	unsigned int	sw;
	unsigned int	quote;
	unsigned int	quote2;
	unsigned int	elcount;

	sw = 0;
	quote = 0;
	quote2 = 0;
	elcount = 0;
	while (*s)
	{
		if (*s == '"' && !quote)
			quote = 1;
		else if (*s == '"' && quote)
			quote = 0;
		if (*s == '\'' && !quote2)
			quote2 = 1;
		else if (*s == '\'' && quote2)
			quote2 = 0;
		if (!del_occ(*s) && !sw && !quote && !quote2)
		{
			sw = 1;
			elcount++;
		}
		else if (del_occ(*s))
			sw = 0;
		s++;
	}
	return (elcount);
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

int	del_occ(char c)
{
	int	i;

	i = 0;
	while (DEL[i])
	{
		if (DEL[i] == c)
			return (1);
		++i;
	}
	return (0);
}

size_t	token_len(const char *s)
{
	const char	*del;

	del = del_strchr((char *)s);
	if (!del)
		return ((size_t)(ft_strchr(s, '\0') - s));
	return ((size_t)(del - s));
}
