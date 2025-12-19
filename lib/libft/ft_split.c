/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbindl <pbindl@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 19:55:30 by pbindl            #+#    #+#             */
/*   Updated: 2025/05/22 17:48:40 by pbindl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static unsigned int	count_elts(const char *s, char c)
{
	unsigned int	elcount;
	unsigned int	sw;

	sw = 0;
	elcount = 0;
	while (*s)
	{
		if (*s != c && sw == 0)
		{
			sw = 1;
			elcount++;
		}
		else if (*s == c)
			sw = 0;
		s++;
	}
	return (elcount);
}

static const char	*skip_separators(const char *in, char c)
{
	while (*in == c)
		in++;
	return (in);
}

static char	**strarr_destruct(char **in, unsigned int n)
{
	while (n >= 0)
		free(in[n--]);
	free(in);
	return (NULL);
}

char	**ft_split(const char *s, char c)
{
	int		elcount;
	char	**out;
	int		i;
	size_t	elen;

	elcount = (int)count_elts(s, c);
	out = ft_calloc(elcount + 1, sizeof(char *));
	if (!out)
		return (NULL);
	i = -1;
	while (++i < elcount)
	{
		s = skip_separators(s, c);
		if (ft_strchr(s, c) == NULL)
			elen = ft_strchr(s, '\0') - s;
		else
			elen = ft_strchr(s, c) - s;
		out[i] = ft_calloc(elen + (elen > 0), 1);
		if (!out[i])
			return (strarr_destruct(out, i));
		ft_strlcpy(out[i], s, elen + (elen > 0));
		s += elen;
	}
	out[i] = NULL;
	return (out);
}
