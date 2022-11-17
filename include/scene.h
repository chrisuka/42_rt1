/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikarjala <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 20:57:29 by ikarjala          #+#    #+#             */
/*   Updated: 2022/11/17 20:58:41 by ikarjala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_H
# define SCENE_H

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
	t_rgb	col;
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


#endif
