/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikarjala <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 21:15:40 by ikarjala          #+#    #+#             */
/*   Updated: 2022/12/05 19:12:10 by ikarjala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H

typedef struct s_rgb_floating
{
	float	r;
	float	g;
	float	b;
}	t_rgbf;

/* Union representing a pixel's colors in a format suitable for a texture.
 * Bit depth of 8 (8 bits or 256 values / channel) in format [AA][RR][GG][BB].
 * Since the Alpha channel is not super useful for rendering,
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
}	t_pixel; // WARN: UNTESTED, DO NOT USE

typedef struct	s_raytrace_data {
	double	qf_roots[2];
	t_vec	hit_point;
	t_vec	hit_normal;
}	t_rt;

enum e_sdl_settings {
	esdl_dev = SDL_INIT_VIDEO,
	esdl_pxformat = SDL_PIXELFORMAT_ARGB8888,
	esdl_winpos = SDL_WINDOWPOS_CENTERED,
	esdl_winflags = SDL_WINDOW_SHOWN
};

t_rgbf			cmul(t_rgbf c, double v);
unsigned int	to_rgb(t_rgbf c);

#endif
