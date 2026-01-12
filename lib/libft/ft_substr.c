/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbindl <pbindl@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 18:18:41 by pbindl            #+#    #+#             */
/*   Updated: 2025/05/22 17:09:11 by pbindl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	char	*startptr;
	size_t	substrlen;
	char	*out;

	if (start >= ft_strlen(s))
		return (ft_strdup(""));
	startptr = (char *)s + start;
	substrlen = ft_strlen(startptr);
	if (substrlen > len)
		substrlen = len;
	out = (char *)malloc(substrlen + 1);
	if (!out)
		return (NULL);
	ft_strlcpy(out, startptr, substrlen + 1);
	return (out);
}
