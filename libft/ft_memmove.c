/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekantane <ekantane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 11:46:26 by ekantane          #+#    #+#             */
/*   Updated: 2021/11/29 17:24:27 by ekantane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t n)
{
	size_t	i;
	char	*str_d;
	char	*str_s;

	i = 0;
	str_d = (char *)dst;
	str_s = (char *)src;
	if (dst == NULL && src == NULL)
		return (NULL);
	if (str_s < str_d)
		while (i++ < n)
			str_d[n - i] = str_s[n - i];
	while (i < n)
	{
		str_d[i] = str_s[i];
		i++;
	}
	return (str_d);
}
