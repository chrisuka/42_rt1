/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekantane <ekantane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 15:31:23 by ekantane          #+#    #+#             */
/*   Updated: 2021/12/06 16:27:19 by ekantane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*node;

	if (lst == NULL || f == NULL)
		return (NULL);
	node = f(lst);
	if (node == NULL)
		return (NULL);
	node->next = ft_lstmap(lst->next, f);
	return (node);
}
