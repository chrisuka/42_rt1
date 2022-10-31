/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekantane <ekantane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 12:42:28 by ekantane          #+#    #+#             */
/*   Updated: 2021/11/29 17:25:20 by ekantane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	d_len;
	size_t	s_len;
	size_t	res;
	size_t	i;

	d_len = ft_strlen(dst);
	s_len = ft_strlen(src);
	res = 0;
	i = 0;
	if (dstsize > d_len)
		res = s_len + d_len;
	else
		res = s_len + dstsize;
	while (src[i] && (d_len + 1) < dstsize)
	{
		dst[d_len] = src[i];
		d_len++;
		i++;
	}
	dst[d_len] = '\0';
	return (res);
}
