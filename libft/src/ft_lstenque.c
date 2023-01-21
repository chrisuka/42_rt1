/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstenque.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikarjala <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 18:09:04 by ikarjala          #+#    #+#             */
/*   Updated: 2023/01/21 19:46:57 by ikarjala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Add a new link to the beginning of *lst* and update the pointer
 * to the new first element.
 *
 * Returns 0 for failure or 1 for success.
*/
int	ft_lstenque(t_list **lst, void *content, const size_t bs)
{
	t_list	*node;

	if (!lst || !content || bs == 0)
		return (0);
	node = (t_list *)malloc(sizeof(t_list));
	if (!node)
		return (0);
	*node = (t_list){
		.content_size = bs, .content = content, .next = *lst};
	*lst = node;
	(*lst)->next = node->next;
	return (1);
}
