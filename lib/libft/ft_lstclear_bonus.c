/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbindl <pbindl@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 19:12:18 by pbindl            #+#    #+#             */
/*   Updated: 2025/05/22 17:06:19 by pbindl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	if (!*lst)
		return ;
	if ((*lst)->next)
		ft_lstclear(&((*lst)->next), del);
	(*del)((*lst)->content);
	free(*lst);
	*lst = NULL;
}
