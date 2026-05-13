/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoll.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbindl <pbindl@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/13 16:17:36 by pbindl            #+#    #+#             */
/*   Updated: 2026/05/13 16:21:06 by pbindl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/utils.h"
#include <errno.h>
#include <limits.h>
#include <stdbool.h>

static bool	check_overflow(const char *nptr, long long out, long long mult)
{
	bool	ret;

	ret = true;
	if (mult == 1 && out > LLONG_MAX / 10)
		ret = false;
	if (mult == -1 && out < LLONG_MIN / 10)
		ret = false;
	if (mult == 1 && out == LLONG_MAX / 10 && (*nptr - '0') > LLONG_MAX % 10)
		ret = false;
	if (mult == -1 && out == LLONG_MIN / 10 && (*nptr - '0') > -(LLONG_MIN
			% 10))
		ret = false;
	if (!ret)
		errno = EINVAL;
	else
		errno = 0;
	return (ret);
}

long long	ft_atoll(const char *nptr)
{
	long long	out;
	long long	mult;

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
		if (!check_overflow(nptr, out, mult))
			return (LONG_MAX);
		out *= 10;
		out += (*nptr - 48) * mult;
		nptr++;
	}
	return (out);
}
