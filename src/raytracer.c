/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikarjala <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/20 21:23:06 by ikarjala          #+#    #+#             */
/*   Updated: 2022/11/30 07:49:52 by ikarjala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

/* Return the normal vector of ray intersection point on an sphere's surface.
 * N = Normalize(P - O)
 * where P = ray hit point, O = object origin
*/
static inline t_vec	sphere_normal(t_vec dir, t_vec hit_p, t_object *obj)
{
	t_vec	n;

	n = vec_norm (vec_sub (hit_p, obj->pos));
	if (vec_dot (dir, n) > EPS)
		return (vec_scale (n, -1));
	return (n);
}

/* Create a ray shooting from camera origin toward a direction
 * determined by the pixel coordinates and frustrum size.
 * Closer to the edges means shooting at a greater angle to create a
 * perspective projection.
*/
t_ray	project_ray_from_camera(int x, int y, t_cam cam)
{
	const double	unit_w = 1.0L / (WIN_W / 2);
	const double	unit_h = 1.0L / (WIN_H / 2);

	return ((t_ray){
		.orig = cam.pos,
		.dir = vec_rot ((t_vec){
			.x = (x - WIN_W / 2) * unit_w * (VIEWPORT_W / WIN_W),
			.y = (y - WIN_H / 2) * unit_h * (VIEWPORT_H / WIN_H),
			.z = 1.0L}, cam.rot)
	});
}

/* Trace the reverse path of a photon traveling from a light source
 * to the camera frustrum and return a color reflected from all the objects
 * it hit on the way.
 *
 * More specifically, test all objects for intersection with ray
 * and mix the object diffuse colors together multiplied by the
 * combined intensities of all affecting light sources.
*/
t_rgbf	raytrace(t_scene *ctx, t_ray ray)
{
	t_rgbf		c;
	t_object	*nearest;
	t_vec		hit_p;
	double		min_t;
	double		t;

	nearest = NULL;
	min_t = INFINITY;
	t = intersect (ray, ctx->obj[0]);
	if (t > 0 && t < min_t)
	{
		min_t = t;
		nearest = &ctx->obj[0];
	}
	if (nearest)
		c = nearest->color;
	else
		return ((t_rgbf){0, 0, 0});

	hit_p = vec_sum (ray.orig, vec_scale (ray.dir, min_t));
	c = cmul (c, get_intensity (
				hit_p,
				sphere_normal (ray.dir, hit_p, nearest),
				ctx->light));

	// TODO: specular
	return (c);
}
