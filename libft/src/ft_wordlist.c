/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wordlist.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikarjala <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 17:32:07 by ikarjala          #+#    #+#             */
/*   Updated: 2022/10/04 21:43:34 by ikarjala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Return a linked list, each link containing one word in the buffer
 * del		delimiter character (replace with isspace ?)
 * len		only search up to this many bytes
*/
t_list	*ft_wordlist(const char *buf, const char *del, size_t len)
{
	t_list	*lst;
	t_list	*n;
	char	*cp;
	char	*ep;

	if (!buf)
		return (NULL);
	n = lst;
	cp = buf;
	while (cp != buf + len)
	{
		cp = ft_memchr_not(cp, del, len);
		if (cp == NULL)
			return (NULL);
		ep = ft_memchr_any(cp, del, len - (cp - buf));
		if (ep == NULL)
			ep = buf + len - 1;
		n->next = ft_lstnew2 (cp, ep - cp); // ERROR
		n = n->next;
	}
	return (lst);
}

/* lstnew2: allocate lst but dont strdup, just point and set size
 * memchr_any: memchr but with several chars to test against
 * memchr_not: inverse of memchr_any; loop until first char that's not one of delims
*/
