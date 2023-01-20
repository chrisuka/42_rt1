/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikarjala <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 16:25:50 by ikarjala          #+#    #+#             */
/*   Updated: 2023/01/20 17:52:25 by ikarjala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

double	ft_atof(const char *str)
{
	const int	decimal = ft_atoi (str);
	double		fractional;
	double		mul;
	char		*cp;

	fractional = 0.00;
	mul = 0.10;
	cp = ft_strchr (str, '.');
	if (!cp)
		return ((double)(1.0 * decimal));
	while (ft_isdigit (*(++cp)))
	{
		fractional += (double)(*cp - '0') *mul;
		mul *= 0.10;
	}
	if (decimal < 0)
		fractional *= -1.0;
	return ((double)(decimal + fractional));
}
