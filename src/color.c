/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekantane <ekantane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 15:16:12 by ikarjala          #+#    #+#             */
/*   Updated: 2023/01/27 18:22:15 by ikarjala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_rgbf	cmul(t_rgbf c, double v)
{
	return ((t_rgbf){
		.r = c.r * v,
		.g = c.g * v,
		.b = c.b * v
	});
}

/* Return a copy of floating-point color c, converted to unsigned integer 32
 * in format ARGB8 (CHAR (8) bits / channel). Clear alpha.
*/
unsigned int	to_rgb(t_rgbf c)
{
	return (((unsigned int)(c.r * 255.0) << (__CHAR_BIT__ * 2)
		| (unsigned int)(c.g * 255.0) << (__CHAR_BIT__ * 1)
		| (unsigned int)(c.b * 255.0) << (__CHAR_BIT__ * 0))
		& ~(0xFF << (__CHAR_BIT__ * 3))
	);
}
