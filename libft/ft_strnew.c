/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekantane <ekantane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/31 16:24:39 by ekantane          #+#    #+#             */
/*   Updated: 2021/11/29 17:25:45 by ekantane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnew(size_t size)
{
	size_t		i;
	char		*mem;

	i = 0;
	mem = (char *)malloc(sizeof(char) * (size + 1));
	if (!(mem))
		return (NULL);
	mem[i] = '\0';
	while (i < size)
	{
		mem[i++] = '\0';
	}
	mem[i] = '\0';
	return (mem);
}
