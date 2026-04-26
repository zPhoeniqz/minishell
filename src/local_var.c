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

	i = 0;
	if ((*av >= '0' && *av <= '9') || *av == '=')
		return (0);
	while (*av && *av != '=')
	{
		if (!key_char(av[i++]))
			return (0);
	}
	if (av[i] != '=')
		return (0);
	return (1);
}
//*/
