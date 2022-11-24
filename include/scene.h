/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikarjala <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 20:57:29 by ikarjala          #+#    #+#             */
/*   Updated: 2022/11/24 18:31:06 by ikarjala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_H
# define SCENE_H

# include "render.h"

typedef struct s_light
{
	t_vec	pos;
	double	inten;
}	t_light;

typedef struct s_object
{
	int		id;
	t_vec	pos;
	t_vec	rot;
	double	r;
	double	specular;
	t_rgbf	color;
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
	t_object	obj[];
	t_light		light;
	double		ambient;
}	t_scene;

#endif
