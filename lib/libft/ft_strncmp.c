/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbindl <pbindl@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 18:38:39 by pbindl            #+#    #+#             */
/*   Updated: 2025/05/22 17:08:59 by pbindl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char	c1;
	unsigned char	c2;

	c2 = *s2++;
	c1 = *s1++;
	while (n-- > 0)
	{
		if (c1 != c2)
			return (c1 - c2);
		c2 = *s2++;
		c1 = *s1++;
		if (!c1 && !c2)
			break ;
	}
	return (0);
}
