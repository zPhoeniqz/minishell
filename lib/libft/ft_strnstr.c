/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbindl <pbindl@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 18:38:39 by pbindl            #+#    #+#             */
/*   Updated: 2025/05/22 17:09:03 by pbindl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t n)
{
	int		j;
	size_t	i;

	i = 0;
	if (ft_strlen(little) == 0)
		return ((char *)big);
	while (big[i])
	{
		j = 0;
		while (big[i] && i < n && big[i] == little[j])
		{
			i++;
			j++;
		}
		if (!little[j])
			return ((char *)&big[i - j]);
		i -= j - 1;
	}
	return (NULL);
}
