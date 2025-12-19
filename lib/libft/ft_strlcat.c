/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbindl <pbindl@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 15:41:01 by pbindl            #+#    #+#             */
/*   Updated: 2025/05/22 17:08:46 by pbindl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	n;
	size_t	dest_len;
	size_t	i;
	size_t	j;

	n = size;
	i = 0;
	while (n-- != 0 && dst[i])
		i++;
	dest_len = i;
	n = size - dest_len;
	if (n == 0)
		return (dest_len + ft_strlen(src));
	j = 0;
	while (src[j])
	{
		if (n != 1)
		{
			dst[i++] = src[j];
			n--;
		}
		j++;
	}
	dst[i] = '\0';
	return (dest_len + j);
}
