/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekantane <ekantane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 21:15:40 by ikarjala          #+#    #+#             */
/*   Updated: 2023/01/20 15:42:34 by ikarjala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H

# include "scene.h"

typedef struct s_rgb_floating
{
	double	r;
	double	g;
	double	b;
}	t_rgbf;

typedef struct s_ray
{
	t_vec	orig;
	t_vec	dir;
}	t_ray;

typedef struct	s_raytrace_data {
	struct s_material	*hit_material;
	t_ray				ray;
	double				qf_roots[2];
	double 				min_t;
	t_vec				hit_point;
	t_vec				hit_normal;
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
