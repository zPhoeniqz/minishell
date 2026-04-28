/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whuth <whuth@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 18:17:18 by whuth             #+#    #+#             */
/*   Updated: 2026/04/28 18:20:22 by whuth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	exec(t_data data)
{
	int		i;
	t_tl	prompt;

	check_here_doc(data);
	i = 0;
	prompt = data->tokenlist;
	while (i < prompt.ll)
	{
		if (prompt->tokens.type == INFILE)
			do;
		if (prompt->tokens.type == OUTFILE)
			do;
		if (prompt->tokens.type == OUTFILEAPPEND)
			do;
		if (prompt->tokens.type == ARGUMENT)
			do;
		if (prompt->tokens.type == PIPE)
			do;
			prompt->tokens = prompt->tokens->next_token;
		++i;
	}
}
