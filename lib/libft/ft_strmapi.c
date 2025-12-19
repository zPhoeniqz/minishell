/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbindl <pbindl@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 20:57:07 by pbindl            #+#    #+#             */
/*   Updated: 2025/05/22 17:09:52 by pbindl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strmapi(const char *s, char (*f)(unsigned int, char))
{
	char			*out;
	size_t			len;
	unsigned int	i;

	len = ft_strlen(s) + 1;
	out = malloc(len);
	if (!out)
		return (NULL);
	ft_strlcpy(out, s, len);
	i = 0;
	while (out[i])
	{
		out[i] = (*f)(i, out[i]);
		i++;
	}
	return (out);
}
