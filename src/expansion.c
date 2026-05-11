/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbindl <pbindl@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/11 19:57:20 by pbindl            #+#    #+#             */
/*   Updated: 2026/05/11 19:58:25 by pbindl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "../inc/utils.h"
#include "../libft/libft.h"
#include <stdbool.h>
#include <stdlib.h>

static bool	replace_var(char **s, char *value, int i, int end)
{
	size_t	nsize;
	char	*out;

	nsize = i + ft_strlen(value) + ft_strlen(*s + end) + 1;
	out = ft_calloc(nsize, 1);
	if (!out)
		return (free(*s), false);
	ft_memcpy(out, *s, i);
	ft_strlcat(out, value, nsize);
	ft_strlcat(out, *s + end, nsize);
	free(*s);
	*s = out;
	return (true);
}

static char	*get_value(char **envp, char **s, int i, int *end)
{
	char	c;
	char	*value;

	while (ft_isalnum((*s)[*end]) || (*s)[*end] == '_')
		(*end)++;
	c = (*s)[*end];
	(*s)[*end] = 0;
	value = ft_getenv(envp, *s + i + 1);
	if (!value)
		value = " ";
	(*s)[*end] = c;
	return (value);
}

static char	*format_exit_code(char **target, int exit_code)
{
	static char	buf[4] = "";
	char		*a;

	a = ft_itoa(exit_code);
	if (!a)
		return (NULL);
	ft_bzero(buf, 4);
	ft_memcpy(buf, a, 3);
	free(a);
	*target = buf;
	return (buf);
}

// replaces the dollar-annotated variable names in s with their corresponding
// value or a blank. s MUST be heap-allocated.
bool	expand_str(char **envp, char **s, int last_exit_code)
{
	char	*value;
	int		i;
	int		end;

	if (!*s)
		return (false);
	i = -1;
	while ((*s)[++i])
	{
		if ((*s)[i] == '$' && ft_isdelim((*s)[i + 1]))
			continue ;
		if ((*s)[i] == '$')
		{
			end = i + 1;
			end += (*s)[end] == '?';
			if ((*s)[end] != '?')
				value = get_value(envp, s, i, &end);
			else if (!format_exit_code(&value, last_exit_code))
				return (free(*s), false);
			if (!replace_var(s, value, i, end))
				return (false);
		}
	}
	return (true);
}
