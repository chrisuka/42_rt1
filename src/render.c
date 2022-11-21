/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikarjala <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/20 21:35:43 by ikarjala          #+#    #+#             */
/*   Updated: 2022/11/21 17:50:17 by ikarjala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#include "render.h"

void	render(t_sdl *sdl)
{
	int x;
	int y;

	SDL_LockSurface (sdl->surf);
	x = -1;
	while (++x < DWIDTH)
	{
		y = -1;
		while (++y < DHEIGHT)
		{
			// for testing, just set every pixel to red
			//sdl->vbuf [x][y] = 0x00FF0000;
		}
	}
	ft_memmove (sdl->surf->pixels, sdl->vbuf, sizeof(sdl->vbuf));
	SDL_UnlockSurface (sdl->surf); 
	SDL_UpdateWindowSurface (sdl->wind);
}
