/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whuth <whuth@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 17:05:25 by whuth             #+#    #+#             */
/*   Updated: 2025/08/02 18:33:34 by whuth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gnl.h"

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == (unsigned char)c)
			return ((char *)s + i);
		++i;
	}
	if (s[i] == (unsigned char)c)
		return ((char *)s + i);
	return (NULL);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	s_l;
	char	*sub;

	if (!s)
		return (NULL);
	if (ft_strlen(s) <= start)
		return (ft_strdup(""));
	if (ft_strlen(s) - start < len)
		s_l = ft_strlen(s) - start;
	else
		s_l = len;
	sub = malloc((s_l + 1) * sizeof(char));
	if (!sub)
		return (NULL);
	i = 0;
	while (i < s_l)
		sub[i++] = s[start++];
	sub[i] = 0;
	return (sub);
}

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		++i;
	return (i);
}

char	*ft_strdup(const char *s)
{
	size_t	i;
	size_t	len;
	char	*ptr;

	len = ft_strlen(s);
	ptr = malloc(len * sizeof(char) + sizeof(char));
	if (!ptr)
		return (NULL);
	i = 0;
	while (i < len)
	{
		*ptr++ = *s++;
		++i;
	}
	*ptr = 0;
	return (ptr - len);
}

char	*ft_strjoin(const char *s1, const char *s2)
{
	size_t	l_1;
	size_t	l_2;
	size_t	i;
	size_t	j;
	char	*sn;

	l_1 = ft_strlen(s1);
	l_2 = ft_strlen(s2);
	sn = malloc((l_1 + l_2 + 1) * sizeof(char));
	if (!sn)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[j])
		sn[i++] = s1[j++];
	while (*s2)
		sn[i++] = *s2++;
	sn[i] = 0;
	return (sn);
}
