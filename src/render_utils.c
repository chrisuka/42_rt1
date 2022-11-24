/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekantane <ekantane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 15:16:56 by ikarjala          #+#    #+#             */
/*   Updated: 2022/11/24 14:32:12 by ikarjala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/rtv1.h"

#if 1
/* Return index position of pixel at (x,y)
*/
static inline unsigned int	px_at(int x, int y)
{
	return (y * WIN_H + x);
}

/* Set the RGB color value of a pixel in the video buffer.
*/
void	set_pixel(t_sdl *sdl, int x, int y, unsigned int color)
{
	sdl->vbuf[px_at(x, y)] = color;
}
#endif
