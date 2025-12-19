/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbindl <pbindl@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 18:38:39 by pbindl            #+#    #+#             */
/*   Updated: 2025/05/22 17:10:03 by pbindl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int				i;
	unsigned char	ch;

	ch = (unsigned char)c;
	i = ft_strlen(s);
	while (s[i] != ch && i > 0)
		i--;
	if (s[i] != ch)
		return (NULL);
	return ((char *)(s + i));
}
