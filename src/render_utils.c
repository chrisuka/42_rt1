/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikarjala <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 15:16:56 by ikarjala          #+#    #+#             */
/*   Updated: 2022/11/17 19:58:58 by ikarjala         ###   ########.fr       */
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

void	set_color(t_sdl *sdl, int x, int y)
{
	double	p;

	if (sdl->light.new_inten > 1)
		sdl->light.new_inten = 1;
	p = sdl->light.new_inten;
	SDL_SetRenderDrawColor(sdl->rend,
			sdl->obj[0].col.rgb[0] * p,
			sdl->obj[0].col.rgb[1] * p,
			sdl->obj[0].col.rgb[2] * p, 255);
	SDL_RenderDrawPoint(sdl->rend, x, y);
}

// SDL_RenderClear == mlx_clear_window
//
// SDL_LockTexture		: lock texture for write-only mode so we can edit safely
// memmove vbuf => tex_buf
// SDL_UnlockTexture	: give texture back read access
//
// SDL_RenderCopy		: copy texture to render target
// SDL_RenderPresent == mlx_put_img_to_window
