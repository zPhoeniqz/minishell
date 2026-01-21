/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbindl <pbindl@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 18:40:18 by pbindl            #+#    #+#             */
/*   Updated: 2025/07/15 15:13:30 by pbindl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"
#include "ft_printf.h"
#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#ifndef FD
# define FD 1
#endif

static int	g_count = 0;

static void	put_ptrhex_fd(uintptr_t p, int uppercase, int fd)
{
	int	i;
	int	v;
	int	started;
	int	(*char_manipulator)(int);

	if (uppercase)
		char_manipulator = ft_toupper;
	else
		char_manipulator = ft_tolower;
	i = (sizeof(p) << 3) - 4;
	started = 0;
	while (i >= 0)
	{
		v = (p >> i) & 0xf;
		started = started || v != 0 || i == 0;
		if (v >= 0 && v < 10 && started)
			ft_putchar_fd(char_manipulator('0' + v), fd);
		else if (started)
			ft_putchar_fd(char_manipulator('a' + v - 10), fd);
		g_count += started;
		i -= 4;
	}
}

static int	handle_hex(const char *fstr, int index, va_list *args)
{
	uintptr_t	p;

	if (fstr[index] == 'p')
	{
		p = (uintptr_t)va_arg(*args, void *);
		if (p == 0)
		{
			ft_putstr_fd("(nil)", FD);
			g_count += 5;
			return (0);
		}
		ft_putstr_fd("0x", FD);
		g_count += 2;
	}
	else
		p = (uintptr_t)va_arg(*args, unsigned int);
	put_ptrhex_fd(p, fstr[index] == 'X', FD);
	return (0);
}

static int	handle_number(const char *fstr, int index, va_list *args)
{
	char	*s;

	if (fstr[index] == 'd' || fstr[index] == 'i')
		s = ft_itoa(va_arg(*args, int));
	else
		s = ft_utoa(va_arg(*args, unsigned int));
	if (!s)
		return (-1);
	ft_putstr_fd(s, FD);
	g_count += ft_strlen(s);
	free(s);
	return (0);
}

static int	handle_placeholder(const char *fstr, int index, va_list *args)
{
	char	*s;

	if (fstr[index] == '%' && ++g_count > 0)
		ft_putchar_fd('%', FD);
	else if (fstr[index] == 'c' && ++g_count > 0)
		ft_putchar_fd(va_arg(*args, int), FD);
	else if (fstr[index] == 's')
	{
		s = va_arg(*args, char *);
		if (!s)
		{
			ft_putstr_fd("(null)", FD);
			g_count += 6;
			return (0);
		}
		ft_putstr_fd(s, FD);
		g_count += ft_strlen(s);
	}
	else if (fstr[index] == 'd' || fstr[index] == 'i' || fstr[index] == 'u')
		return (handle_number(fstr, index, args));
	else
		return (handle_hex(fstr, index, args));
	return (0);
}

int	ft_printf(const char *fstr, ...)
{
	va_list	args;
	int		i;

	va_start(args, fstr);
	i = 0;
	g_count = 0;
	while (fstr[i])
	{
		if (fstr[i] == '%')
		{
			if (handle_placeholder(fstr, ++i, &args) < 0)
				return (-1);
		}
		else
		{
			ft_putchar_fd(fstr[i], FD);
			g_count++;
		}
		i++;
	}
	return (g_count);
}
