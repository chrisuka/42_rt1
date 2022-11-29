/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikarjala <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/20 21:23:06 by ikarjala          #+#    #+#             */
/*   Updated: 2022/11/29 19:30:28 by ikarjala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

/* Return the normal vector of ray intersection point on an object's surface.
 * n = Normalize(P - O)
 * where P = ray hit point, O = object origin
*/
static inline t_vec	sphere_normal(t_vec dir, t_vec hit_p, t_object *obj)
{
	t_vec	n;

	n = vec_norm(vec_sub(hit_p, obj->pos));
	if (vec_dot(dir, n) > EPS)
		return (vec_scale (n, -1));
	return (n);
}

static inline t_vec	get_dir(double x, double y, t_vec cam_rot)
{
	return (vec_rot ((t_vec){
		.x = x * (VIEWPORT_W / WIN_W),
		.y = y * (VIEWPORT_H / WIN_H),
		.z = 1.0L}, cam_rot));
}

t_ray	project_ray_from_camera(int x, int y, t_cam cam)
{
	const double	w_frac = 1.0L / (WIN_W / 2);
	const double	h_frac = 1.0L / (WIN_H / 2);
	const double	mapx = (x - WIN_W / 2) * w_frac;
	const double	mapy = (y - WIN_H / 2) * h_frac;

	return ((t_ray){
		.orig = cam.pos,
		.dir = get_dir (mapx, mapy, cam.rot)
	});
}

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
