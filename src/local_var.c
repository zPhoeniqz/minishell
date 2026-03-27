/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   local_var.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whuth <whuth@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 16:18:03 by whuth             #+#    #+#             */
/*   Updated: 2026/03/24 18:11:06 by whuth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*
static int	key_char(char c)
{
	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0'
			&& c <= '9') || c == '_');
}


int	check_legit_var(int ac, char **av)
{
	int	i;

	if (ac != 2)
		return (0);
	i = 0;
	if ((av[1][i] >= '0' && av[1][i] <= '9') || av[1][i] == '=')
		return (0);
	while (av[1][i] && av[1][i] != '=')
	{
		if (!key_char(av[1][i++]))
			return (0);
	}
	if (av[1][i] != '=')
		return (0);
	return (1);
}
//*/
