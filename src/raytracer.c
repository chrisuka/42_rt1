/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikarjala <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/20 21:23:06 by ikarjala          #+#    #+#             */
/*   Updated: 2022/11/21 22:10:34 by ikarjala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static inline t_vec	get_dir(double x, double y, t_vec cam_rot)
{
	return (vec_rot ((t_vec){
		.x = x * (double)(V_W / DWIDTH),
		.y = y * (double)(V_W / DWIDTH),
		.z = 1.0L}, cam_rot));
}

t_ray	project_ray_from_camera(t_cam cam)
{
	const double	mapx = cam.pos.x - (DWIDTH / 2);
	const double	mapy = cam.pos.y - (DHEIGHT / 2);

	return ((t_ray){
		.orig = cam.pos,
		.dir = get_dir (mapx, mapy, cam.rot)
	});
}

# if 0
t_rgbf	raycast(t_ray)
{
	return ((t_rgbf){0, 0, 0});
}
#endif
