/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mem.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbindl <pbindl@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 14:37:13 by pbindl            #+#    #+#             */
/*   Updated: 2025/05/22 17:31:26 by pbindl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char	*p;

	if (n == 0)
		return (NULL);
	p = (const unsigned char *)s;
	while (*p != (unsigned char)c && --n > 0)
		p++;
	if (*p != (unsigned char)c)
		return (NULL);
	return ((void *)p);
}

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*p1;
	const unsigned char	*p2;
	char				c1;
	char				c2;

	p1 = (const unsigned char *)s1;
	p2 = (const unsigned char *)s2;
	while (n-- > 0)
	{
		c1 = *p1++;
		c2 = *p2++;
		if (c1 != c2)
		{
			if (p1[-1] < p2[-1])
				return (-1);
			else
				return (1);
		}
	}
	return (0);
}

void	*ft_memset(void *s, int c, size_t n)
{
	char	*cs;

	cs = (char *)s;
	while (n-- > 0)
		*cs++ = c;
	return (s);
}

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char		*d;
	const char	*s;

	if (!dst && !src)
		return (NULL);
	d = (char *)dst;
	s = (const char *)src;
	while (n-- > 0)
		*d++ = *s++;
	return (dst);
}

void	*ft_memmove(void *dst, const void *src, size_t n)
{
	char		*d;
	const char	*s;

	d = (char *)dst;
	s = (const char *)src;
	if (src > dst)
	{
		while (n-- > 0)
			*d++ = *s++;
	}
	else if (src < dst)
	{
		d += n - 1;
		s += n - 1;
		while (n-- > 0)
			*d-- = *s--;
	}
	return (dst);
}
