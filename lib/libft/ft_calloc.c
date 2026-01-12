/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbindl <pbindl@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 15:44:13 by pbindl            #+#    #+#             */
/*   Updated: 2025/05/19 23:03:11 by pbindl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdint.h>
#include <stdlib.h>

void	*ft_calloc(size_t nmemb, size_t size)
{
	char	*out;

	if ((nmemb > 2147483648 || size > 2147483648) && SIZE_MAX / nmemb < size)
		return (NULL);
	out = (char *)malloc(nmemb * size);
	if (!out)
		return (NULL);
	ft_bzero(out, size * nmemb);
	return (out);
}
