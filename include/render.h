/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekantane <ekantane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 21:15:40 by ikarjala          #+#    #+#             */
/*   Updated: 2023/01/25 16:25:39 by ikarjala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H

# include "vector.h"
# include "scene.h"

typedef struct s_ray			t_ray;
typedef struct s_material		t_mat;
typedef struct s_object			t_obj;
typedef struct s_scene_context	t_scene;
typedef double					(*t_rayfn)(t_ray r, t_obj o);

typedef struct s_quadfn_container
{
	double	a;
	double	b;
	double	c;
}	t_quad;

typedef struct s_light
{
	t_vec	pos;
	double	intensity;
}	t_light;

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

typedef struct s_raytrace_data {
	t_scene	*ctx;
	t_mat	*hit_material;
	t_ray	ray;
	double	min_t;
	t_vec	hit_point;
	t_vec	hit_normal;
}	t_rt;

enum e_sdl_settings {
	esdl_dev = SDL_INIT_VIDEO,
	esdl_pxformat = SDL_PIXELFORMAT_ARGB8888,
	esdl_winpos = SDL_WINDOWPOS_CENTERED,
	esdl_winflags = SDL_WINDOW_SHOWN
};

#endif
