/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   local_var.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whuth <whuth@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 16:18:03 by whuth             #+#    #+#             */
/*   Updated: 2026/01/26 17:47:20 by whuth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/localvar.h"
#include "../inc/minishell.h"

static int	key_char(char c)
{
	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0'
			&& c <= '9') || c == '_');
}

// only one arg
// no whitespace
// start with [A-Za-z_]
// additional can contain numbers [0-9]
// only one '=', before is the key, after is the assigned value
// special chars only in value not in key -> my.var nope; myvar=.100 yop
// if value is in quotations,
// the rules above dont matter.string can be anything

static int	check_legit_var(int ac, char **av)
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

void	save_var(char *s, t_lv **var_list)
{
	t_lv	*tmp;
	t_lv	*new;

	new = malloc(sizeof(t_lv));
	new->key = ft_strcdup(s, '=');
	new->dq = 0;
	while (*s && *s != '=')
		++s;
	if (*(++s) == '\"')
	{
		++s;
		new->dq = 1;
	}
	if (new->dq)
		new->value = ft_strcdup(s, '\"');
	else
		new->value = ft_strcdup(s, 0);
	new->next = NULL;
	if (*var_list == NULL)
		*var_list = new;
	else
	{
		tmp = *var_list;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

void	free_var_list(t_lv **var_list)
{
	t_lv	*tmp;

	if (!var_list || !*var_list)
		return ;
	while (*var_list)
	{
		tmp = (*var_list)->next;
		free((*var_list)->key);
		free((*var_list)->value);
		free(*var_list);
		*var_list = tmp;
	}
	*var_list = NULL;
}

//*/
static void	print_var_list(t_lv **var_list)
{
	t_lv	*tmp;

	tmp = *var_list;
	while (tmp)
	{
		printf("key:\t%s\nvalue:\t%s\ndq:\t%d\n\n", tmp->key, tmp->value,
			tmp->dq);
		tmp = tmp->next;
	}
}

int	main(int ac, char **av)
{
	t_lv	*var_list;

	if (!check_legit_var(ac, av))
	{
		free(av);
		return (1);
	}
	var_list = NULL;
	save_var(av[1], &var_list);
	print_var_list(&var_list);
	free_var_list(&var_list);
	return (0);
}
//*/
