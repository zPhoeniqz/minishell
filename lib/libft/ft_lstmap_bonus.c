/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbindl <pbindl@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 19:48:09 by pbindl            #+#    #+#             */
/*   Updated: 2025/05/28 19:15:09 by pbindl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*head;
	void	*content;

	if (!lst)
		return (NULL);
	content = (*f)(lst->content);
	head = ft_lstnew(content);
	if (!head)
	{
		(*del)(content);
		return (NULL);
	}
	if (!lst->next)
		return (head);
	head->next = ft_lstmap(lst->next, f, del);
	if (!head->next)
	{
		(*del)(head->content);
		free(head);
		return (NULL);
	}
	return (head);
}
