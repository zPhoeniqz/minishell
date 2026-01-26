/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whuth <whuth@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 16:51:36 by whuth             #+#    #+#             */
/*   Updated: 2026/01/26 17:04:59 by whuth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*ft_strcdup(const char *s, char c)
{
	int		i;
	char	*copy;

	i = 0;
	while (s[i] != c && s[i])
		++i;
	if (!(copy = malloc(sizeof(char) * i + 1)))
		return (NULL);
	i = 0;
	while (s[i] != c)
	{
		copy[i] = s[i];
		++i;
	}
	copy[i] = 0;
	return (copy);
}
/*/
int	main(void)
{
	char	*s;
	char	*t;
	char	del;

	s = "myvar=100";
	del = '=';
	t = ft_strcdup(s, del);
	printf("%s\n", t);
	free(t);
	return (1);
}
//*/
