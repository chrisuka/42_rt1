/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekantane <ekantane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 11:46:26 by ekantane          #+#    #+#             */
/*   Updated: 2021/11/29 17:24:13 by ekantane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	size_t			i;
	unsigned char	*str_d;
	unsigned char	*str_s;
	unsigned char	*ptr;
	unsigned char	a;

	i = 0;
	str_d = (unsigned char *)dst;
	str_s = (unsigned char *)src;
	ptr = 0;
	a = (unsigned char)c;
	while (i < n)
	{
		str_d[i] = str_s[i];
		if (str_s[i] == a)
		{
			ptr = str_d + i + 1;
			break ;
		}
		i++;
	}
	return (ptr);
}
