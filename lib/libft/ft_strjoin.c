/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbindl <pbindl@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 18:24:23 by pbindl            #+#    #+#             */
/*   Updated: 2025/05/22 17:08:42 by pbindl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strjoin(const char *s1, const char *s2)
{
	size_t	len;
	char	*out;

	len = ft_strlen(s1) + ft_strlen(s2) + 1;
	out = (char *)malloc(len);
	if (!out)
		return (NULL);
	ft_strlcpy(out, s1, len);
	ft_strlcat(out, s2, len);
	return (out);
}
