/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utoa64.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikarjala <ikarjala@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 19:28:59 by ikarjala          #+#    #+#             */
/*   Updated: 2022/08/19 19:29:00 by ikarjala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_utoa64(unsigned long long n)
{
	char	*str;
	int		c_digits;

	c_digits = ft_log10(n) + 1;
	str = (char *)malloc(sizeof(char) * (size_t)(c_digits + 1));
	if (!str)
		return (NULL);
	str += c_digits;
	*str = '\0';
	while (c_digits-- > 0)
	{
		*(--str) = (char)(n % 10 + '0');
		n /= 10;
	}
	return (str);
}
