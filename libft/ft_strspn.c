/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strspn.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekantane <ekantane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 17:33:22 by ekantane          #+#    #+#             */
/*   Updated: 2021/12/06 14:40:41 by ekantane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

size_t	ft_strspn(const char *str1, const char *str2)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (str1[i] && str2[j])
	{
		i++;
		if (i != j)
			j++;
	}
	return (i);
}
