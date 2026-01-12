/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbindl <pbindl@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 16:51:55 by pbindl            #+#    #+#             */
/*   Updated: 2025/07/15 15:13:39 by pbindl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"
#include <stdlib.h>

static char	*handle_zero(void)
{
	char	*buffer;

	buffer = malloc(2);
	if (!buffer)
		return (NULL);
	buffer[0] = '0';
	buffer[1] = '\0';
	return (buffer);
}

char	*ft_utoa(int value)
{
	unsigned int	uval;
	int				i;
	char			*buffer;
	char			temp[11];
	int				j;

	i = 0;
	uval = (unsigned int)value;
	if (uval == 0)
		return (handle_zero());
	while (uval > 0)
	{
		temp[i++] = (uval % 10) + '0';
		uval /= 10;
	}
	buffer = malloc(i + 1);
	if (!buffer)
		return (NULL);
	j = -1;
	while (++j < i)
		buffer[j] = temp[i - j - 1];
	buffer[i] = '\0';
	return (buffer);
}
