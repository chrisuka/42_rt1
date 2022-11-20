/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikarjala <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 21:15:40 by ikarjala          #+#    #+#             */
/*   Updated: 2022/11/20 20:04:08 by ikarjala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H

typedef struct s_rgb
{
	float	r;
	float	g;
	float	b;
}	t_rgb;

/* Union representing a pixel's colors in a format suitable for a texture.
 * Bit depth of 8 (8 bits or 256 values / channel) in format [AA][RR][GG][BB].
 * Since the Alpha channel is not useful for rendering,
 * we can use it to store metadata instead.
*/
typedef union u_pixel32 {
	unsigned int	c : 32;
	union u_metadata {
		unsigned int	v : 8;
	}	meta;
	unsigned int	a : 8;
	unsigned int	r : 8;
	unsigned int	g : 8;
	unsigned int	b : 8;
}	t_pixel;

enum e_sdl_init_flags {
	esdl_dev = SDL_INIT_VIDEO,
	esdl_pxformat = SDL_PIXELFORMAT_RGBA8888
};

#endif
