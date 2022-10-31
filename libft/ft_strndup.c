/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekantane <ekantane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 17:33:22 by ekantane          #+#    #+#             */
/*   Updated: 2021/12/03 19:04:42 by ekantane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(const char *s1, size_t n)
{
	size_t	len;
	size_t	i;
	char	*dup;

	len = ft_strlen(s1);
	i = 0;
	if (s1 == NULL)
		return (NULL);
	dup = (char *)malloc(sizeof(char) * (len - (len - n)) + 1);
	if (dup == NULL)
		return (NULL);
	while (i < n && i < len)
	{
		dup[i] = s1[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}
