/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strconv.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbindl <pbindl@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 20:35:13 by pbindl            #+#    #+#             */
/*   Updated: 2025/05/22 16:34:32 by pbindl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static void	ft_strrev(char *const s)
{
	size_t	i;
	size_t	j;
	char	c;

	i = 0;
	j = ft_strlen(s) - 1;
	while (i < j)
	{
		c = s[i];
		s[i] = s[j];
		s[j] = c;
		i++;
		j--;
	}
}

static void	ltoa_buf(long n, char *const s)
{
	int	i;
	int	on;

	on = n;
	if (on < 0)
		n = -n;
	i = 0;
	s[i++] = n % 10 + '0';
	n /= 10;
	while (n != 0)
	{
		s[i++] = n % 10 + '0';
		n /= 10;
	}
	if (on < 0)
		s[i++] = '-';
	s[i] = '\0';
	ft_strrev(s);
}

char	*ft_itoa(int n)
{
	int		on;
	int		count;
	char	*buf;

	on = n;
	count = 0;
	if (n == 0)
		count = 1;
	while (n != 0)
	{
		count++;
		n /= 10;
	}
	buf = (char *)malloc(count + 1 + (on < 0));
	if (!buf)
		return (NULL);
	ltoa_buf((long)on, buf);
	return (buf);
}

int	ft_atoi(const char *nptr)
{
	int	out;
	int	mult;

	out = 0;
	mult = 1;
	while ((*nptr >= 9 && *nptr <= 13) || *nptr == 32)
		nptr++;
	if (*nptr == '-')
		mult = -1;
	if (*nptr == '-' || *nptr == '+')
		nptr++;
	while (*nptr >= '0' && *nptr <= '9')
	{
		out *= 10;
		out += (*nptr - 48) * mult;
		nptr++;
	}
	return (out);
}
