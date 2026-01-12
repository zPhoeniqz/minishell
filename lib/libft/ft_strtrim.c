/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbindl <pbindl@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 18:36:39 by pbindl            #+#    #+#             */
/*   Updated: 2025/05/22 17:09:07 by pbindl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static char	*ft_strltrim(const char *s1, const char *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (*s1 == set[i])
			return (ft_strltrim(s1 + 1, set));
		i++;
	}
	return ((char *)s1);
}

static char	*ft_strrtrim(const char *const start, const char *end,
		const char *set)
{
	int	i;

	i = 0;
	while (set[i] && end > start)
	{
		if (*end == set[i])
			return (ft_strrtrim(start, end - 1, set));
		i++;
	}
	return ((char *)end);
}

char	*ft_strtrim(const char *s1, const char *set)
{
	char	*ltrim;
	char	*rtrim;
	char	*out;
	size_t	len;

	if (ft_strlen(s1) == 0 || ft_strlen(set) == 0)
		return (ft_strdup(s1));
	ltrim = ft_strltrim(s1, set);
	rtrim = ft_strrtrim(ltrim, s1 + ft_strlen(s1) - 1, set);
	len = rtrim - ltrim + 1;
	out = malloc(len + 1);
	if (!out)
		return (NULL);
	ft_strlcpy(out, ltrim, len + 1);
	return (out);
}
