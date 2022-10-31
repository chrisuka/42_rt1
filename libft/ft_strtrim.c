/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekantane <ekantane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/31 16:24:39 by ekantane          #+#    #+#             */
/*   Updated: 2021/11/30 16:24:49 by ekantane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	get_beg(char const *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] != ' ' && s[i] != '\n' && s[i] != '\t')
			return ((char)i);
		i++;
	}
	return (-1);
}

static char	get_end(char const *s)
{
	int	i;

	i = (int)(ft_strlen(s) - 1);
	while (s[i])
	{
		if (s[i] != ' ' && s[i] != '\n' && s[i] != '\t')
			return ((char)i);
		i--;
	}
	return (-1);
}

char	*ft_strtrim(char const *s)
{
	int		beg;
	int		end;
	char	*new_s;

	beg = get_beg(s);
	end = get_end(s);
	new_s = (char *)malloc(sizeof(char) * ft_strlen(s) + 1);
	if (!new_s)
		return (NULL);
	if (beg == -1 || end == -1)
		return (ft_strnew(0));
	new_s = ft_strsub(s, (unsigned int)beg, (unsigned int)(end - beg + 1));
	return (new_s);
}
