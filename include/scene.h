/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikarjala <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 20:57:29 by ikarjala          #+#    #+#             */
/*   Updated: 2022/11/21 17:26:41 by ikarjala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_H
# define SCENE_H

# include "render.h"

typedef struct s_light
{
	t_vec	pos;
	t_vec	p;
	t_vec	n;
	double	inten;
	double	new_inten;
}	t_light;

typedef struct s_object
{
	t_vec	pos;
	t_rgbf	col;
	t_vec	rot;
	double	r;
	double	t;
	int		name;
	double	specular;
}	t_object;

typedef struct s_cam
{
	t_vec	pos;
	t_vec	rot;
}	t_cam;

typedef struct s_ray
{
	t_vec	orig;
	t_vec	dir;
}	t_ray;

typedef struct s_scene_context {
	t_cam		cam;
	t_object	obj;
	double		min_t;
	int			clos_obj;
	double		ambient;
	t_light		light;
	int			spl_res[0];
}	t_scene;

#endif
