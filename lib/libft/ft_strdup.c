/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbindl <pbindl@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 17:25:31 by pbindl            #+#    #+#             */
/*   Updated: 2025/05/22 17:08:36 by pbindl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strdup(const char *s)
{
	char	*out;
	size_t	size;

	size = ft_strlen(s) + 1;
	out = (char *)malloc(size);
	if (!out)
		return (NULL);
	ft_strlcpy(out, s, size);
	return (out);
}
