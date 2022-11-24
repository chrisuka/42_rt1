/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikarjala <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/20 21:23:06 by ikarjala          #+#    #+#             */
/*   Updated: 2022/11/24 10:34:11 by ikarjala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

# if 1
static inline t_vec	get_dir(double x, double y, t_vec cam_rot)
{
	return (vec_rot ((t_vec){
		.x = x * (double)(V_W / WIN_W),
		.y = y * (double)(V_H / WIN_H),
		.z = 1.0L}, cam_rot));
}

t_ray	project_ray_from_camera(t_cam cam)
{
	const double	mapx = cam.pos.x - (WIN_W / 2);
	const double	mapy = cam.pos.y - (WIN_H / 2);

	return ((t_ray){
		.orig = cam.pos,
		.dir = get_dir (mapx, mapy, cam.rot)
	});
}

t_rgbf	raytrace(t_ray ray)
{
	ray = (t_ray){{0},{0}};
	return ((t_rgbf){1.0L, 0.0L, 0.0L});
}
#endif
