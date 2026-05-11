/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbindl <pbindl@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/11 20:01:32 by pbindl            #+#    #+#             */
/*   Updated: 2026/05/11 20:02:26 by pbindl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include <errno.h>
#include <stdbool.h>
#include <unistd.h>

char	*ft_getenv(char **envp, const char *name)
{
	size_t	len;
	char	*eqs;

	len = ft_strlen(name);
	while (*envp)
	{
		if (ft_strncmp(*envp, name, len) == 0)
		{
			eqs = ft_strchr(*envp, '=');
			if (!eqs)
				return (NULL);
			return (eqs + 1);
		}
		envp++;
	}
	return (NULL);
}

bool	ft_isspace(char c)
{
	return (c == ' ' || c == '\f' || c == '\n' || c == '\r' || c == '\t'
		|| c == '\v');
}

void	syntaxerr(char invalid)
{
	ft_putstr_fd("Syntax error near '", STDERR_FILENO);
	ft_putchar_fd(invalid, STDERR_FILENO);
	ft_putendl_fd("'", STDERR_FILENO);
	errno = EINVAL;
}
