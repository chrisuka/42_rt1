/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekantane <ekantane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 11:46:26 by ekantane          #+#    #+#             */
/*   Updated: 2021/11/29 17:24:16 by ekantane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*str;
	unsigned char	*foundit;

	str = (unsigned char *)s;
	foundit = NULL;
	while (str != NULL && (n--))
	{
		if (*str != (unsigned char)c)
		{
			str++;
		}
		else
		{
			foundit = str;
			break ;
		}
	}
	return (foundit);
}
