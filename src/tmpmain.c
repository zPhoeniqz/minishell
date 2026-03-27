/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tmpmain.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whuth <whuth@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 15:56:57 by whuth             #+#    #+#             */
/*   Updated: 2026/03/24 18:18:32 by whuth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	free_token_list(t_tl *tl)
{
	int	i;

	if (!tl)
		return ;
	i = 0;
	if (tl->tokens)
	{
		while (i < tl->ll)
			free(tl->tokens[i++]);
		free(tl->tokens);
	}
	free(tl);
}

void	free_all(t_data *data)
{
	if (!data)
		return ;
	free_token_list(data->tl);
	free(data);
}

int	main(void)
{
	t_data	*data;
	char	*input;
	char	*varname[2];
	char	*value[2];

	data = malloc(sizeof(t_data));
	if (!data)
		return (1);
	data->tl = malloc(sizeof(*data->tl));
	if (!data->tl)
	{
		free(data);
		return (1);
	}
	data->tl->tokens = NULL;
	data->tl->ll = 0;
	varname[0] = "name";
	varname[1] = "age";
	value[0] = "wasja";
	value[1] = "one";
	export(varname, value, 2);
	input = "Im $name and Im $age , ok you are $all";
	gettokens(input, data);
	for (int i = 0; i < data->tl->ll; ++i)
		printf("out\t\"%s\"\n", data->tl->tokens[i]);
	free_all(data);
	return (0);
}
//*/
