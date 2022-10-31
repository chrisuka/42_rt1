/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekantane <ekantane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 12:42:28 by ekantane          #+#    #+#             */
/*   Updated: 2021/11/29 17:25:32 by ekantane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncat(char *s1, const char *s2, size_t n)
{
	int	j;
	int	k;

	j = 0;
	k = 0;
	if ((s1 == NULL && s2 == NULL))
		return (NULL);
	while (s1[j] != '\0')
	{
		j++;
	}
	while (s2[k] != '\0' && n > 0)
	{	
		s1[j] = s2[k];
		j++;
		k++;
		n--;
	}
	s1[j] = '\0';
	return (s1);
}
