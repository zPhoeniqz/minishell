/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbindl <pbindl@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/10 21:45:37 by pbindl            #+#    #+#             */
/*   Updated: 2026/05/10 21:55:27 by pbindl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include <stdbool.h>
#include <stddef.h>

int	find_var(char **envp, char *varname)
{
	size_t	len;
	int		i;

	if (!varname)
		return (-2);
	len = ft_strlen(varname);
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], varname, len) == 0)
			return (i);
		i++;
	}
	return (-1);
}

bool	check_varname(const char *name)
{
	if (!ft_isalpha(*name) && *name != '_')
		return (false);
	while (*name)
	{
		if (!ft_isalnum(*name) && *name != '_')
			return (false);
		name++;
	}
	return (true);
}
