/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekantane <ekantane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 15:16:12 by ikarjala          #+#    #+#             */
/*   Updated: 2022/11/18 15:10:24 by ekantane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/rtv1.h"

/* Return a copy of floating-point color c, converted to unsigned integer 32
 * in format: A R G B   (8 bits / channel)
*/
/*
unsigned int	to_rgb(t_color c)
{
	return (
		(unsigned int)(c.r * 255) << (__CHAR_BIT__ * 2) |
		(unsigned int)(c.g * 255) << (__CHAR_BIT__ * 1) |
		(unsigned int)(c.b * 255) << (__CHAR_BIT__ * 0)
		& (0xFF << (__CHAR_BIT__ * 3))
	);
}
*/