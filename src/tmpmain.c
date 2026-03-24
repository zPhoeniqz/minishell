/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tmpmain.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whuth <whuth@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 15:56:57 by whuth             #+#    #+#             */
/*   Updated: 2026/03/18 13:04:06 by whuth            ###   ########.fr       */
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

void	free_var_list(t_vl *var_list)
{
	t_vl	*tmp;

	while (var_list)
	{
		tmp = var_list->next;
		free(var_list->key);
		free(var_list->value);
		free(var_list);
		var_list = tmp;
	}
}

void	free_all(t_data *data)
{
	if (!data)
		return ;
	free_var_list(data->vl);
	free_token_list(data->tl);
	free(data);
}

/*/
static void	print_var_list(t_vl *var_list)
{
	t_vl	*tmp;

	tmp = var_list;
	while (tmp)
	{
		printf("\nkey:\t%s\nvalue:\t%s\ndq:\t%d\n\n", tmp->key, tmp->value,
			tmp->dq);
		tmp = tmp->next;
	}
}
/*/
int	main(void)
{
	t_data	*data;
	char	*input;
	char	*varin[2];

	data = malloc(sizeof(t_data));
	if (!data)
		return (1);
	data->vl = NULL;
	data->tl = malloc(sizeof(*data->tl));
	if (!data->tl)
	{
		free(data);
		return (1);
	}
	data->tl->tokens = NULL;
	data->tl->ll = 0;
	varin[0] = "a.out";
	varin[1] = "name=wasjahuth";
	if (check_legit_var(2, varin))
		save_var(varin[1], &data->vl);
	input = "abcd $name";
	gettokens(input, data);
	for (int i = 0; i < data->tl->ll; ++i)
		printf("%s\n", data->tl->tokens[i]);
	free_all(data);
	return (0);
}
//*/
