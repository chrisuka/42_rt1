/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekantane <ekantane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 15:16:56 by ikarjala          #+#    #+#             */
/*   Updated: 2022/11/20 21:58:42 by ikarjala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/rtv1.h"

#if 0
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

void	set_color(t_sdl *sdl, int i, int x, int y)
{
	double	p;

	if (sdl->light.new_inten > 1)
		sdl->light.new_inten = 1;
	p = sdl->light.new_inten;
	if (i == 1)
	{
	SDL_SetRenderDrawColor(sdl->rend,
			sdl->obj.col.r * p,
			sdl->obj.col.g * p,
			sdl->obj.col.b * p, 255);
	SDL_RenderDrawPoint(sdl->rend, x, y);
	}
	else
	{
		SDL_SetRenderDrawColor(sdl->rend, 0, 0, 0, 255);
		SDL_RenderDrawPoint(sdl->rend, x, y);
	}
}
