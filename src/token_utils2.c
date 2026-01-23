/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whuth <whuth@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 15:32:16 by whuth             #+#    #+#             */
/*   Updated: 2026/01/23 15:36:59 by whuth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	is_paren(char c)
{
	return (c == '(' || c == ')');
}

char	**strarr_destruct(char **in, int n)
{
	while (n >= 0)
		free(in[n--]);
	free(in);
	return (NULL);
}

int	del_occ(char c)
{
	int	i;

	i = 0;
	while (DEL[i])
	{
		if (DEL[i] == c)
			return (1);
		++i;
	}
	return (0);
}

int	is_sep(char c)
{
	return (del_occ(c) && !is_paren(c));
}
