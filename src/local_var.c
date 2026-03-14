/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   local_var.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whuth <whuth@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 16:18:03 by whuth             #+#    #+#             */
/*   Updated: 2026/01/28 17:29:42 by whuth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

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

char	*find_val(char *s, t_vl **vl)
{
	int		i;
	char	*tmp_key;
	char	*out_val;

	i = 0;
	while (!del_occ(s[i]))
		++i;
	if (!(tmp_key = malloc(sizeof(char) * i)))
		return (NULL);
	ft_strlcpy(tmp_key, s, i);
	while (*vl)
	{
		if (!ft_strncmp((*vl)->key, tmp_key, i))
		{
			if (!(out_val = malloc(sizeof(char) * (ft_strlen((*vl)->value) + 1))))
				return (free(tmp_key), NULL);
			ft_strlcpy(out_val, (*vl)->value, ft_strlen((*vl)->value) + 1);
			return (free(tmp_key), out_val);
		}
		*vl = (*vl)->next;
	}
	return (free(tmp_key), NULL);
}

char	*dqvar(char *s, t_vl **vl)
{
	int		i;
	char	*out;
	char	*tmp_val;


	i = 0;
	if (!(out = malloc(sizeof(char) * ft_strlen(s))))
		return (NULL);
	while (s[i])
	{
		if (s[i] == '$')
		{
			tmp_val = find_val(s + i, vl);
			ft_strlcat(out, tmp_val, ft_strlen(out) + ft_strlen(tmp_val));
			i += ft_strlen(tmp_val);
		}
		out[i] = s[i];
		++i;
	}
	return (out);
}

void	save_var(char *s, t_vl **var_list)
{
	t_vl	*tmp;
	t_vl	*new;

	new = malloc(sizeof(t_vl));
	new->key = ft_strcdup(s, '=');
	new->dq = 0;
	while (*s && *s != '=')
		++s;
	if (*(++s) == '\"')
		new->dq = 1;
	if (new->dq)
		new->value = dqvar(++s, var_list);
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
