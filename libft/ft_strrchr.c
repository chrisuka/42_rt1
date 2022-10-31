/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekantane <ekantane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 15:40:32 by ekantane          #+#    #+#             */
/*   Updated: 2021/11/29 17:25:51 by ekantane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	len;

	len = (int)(ft_strlen(s));
	while (len >= 0)
	{
		if (s[len] == c)
			return (&((char *)s)[len]);
		len--;
	}
	return (NULL);
}
