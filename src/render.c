/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikarjala <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/20 21:35:43 by ikarjala          #+#    #+#             */
/*   Updated: 2022/11/21 22:10:27 by ikarjala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#include "render.h"

void	render(t_sdl *sdl)
{
	int	x;
	int	y;
	//unsigned int	*px; // if we want to iterate the surface buffer directly

	SDL_LockSurface (sdl->surf);
	x = -1;
	while (++x < DWIDTH)
	{
		y = -1;
		while (++y < DHEIGHT)
		{
			//sdl->vbuf [x][y] = raytrace (project_ray_from_camera (sdl->cam));
		}
	}
	ft_memmove (sdl->surf->pixels, sdl->vbuf, sizeof(sdl->vbuf));
	SDL_UnlockSurface (sdl->surf); 
	SDL_UpdateWindowSurface (sdl->wind);
}
