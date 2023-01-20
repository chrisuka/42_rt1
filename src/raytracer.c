/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekantane <ekantane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/20 21:23:06 by ikarjala          #+#    #+#             */
/*   Updated: 2023/01/20 15:05:37 by ikarjala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static inline t_ray	project_ray_from_light(t_light light, t_vec hit_point)
{
	return ((t_ray){
		.orig = hit_point,
		.dir = vec_norm(vec_sub(light.pos, hit_point))
	});
}

static inline t_obj*	find_nearest(t_scene *ctx, t_ray ray, double *min_t)
{
	t_obj	*nearest;
	size_t	n;
	double	t;

	nearest = NULL;
	t = 0;
	n = 0;
	while (n < ctx->obj_count)
	{
		t = intersect (ray, ctx->obj[n]);
		if (t > EPS && t < *min_t)
		{
			*min_t = t;
			nearest = &ctx->obj[n];
		}
		n ++;
	}
	return (nearest);
}

/* Create a ray shooting from camera origin toward a direction
 * determined by the pixel coordinates and frustrum size.
 * Closer to the edges means shooting at a greater angle to create a
 * perspective projection.
*/
t_ray	project_ray_from_camera(int x, int y, t_cam cam)
{
	const double	unit_w = 1.0L / (WIN_W / 2);
	const double	unit_h = 1.0L / (WIN_H / 2) * -1;

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
	t_rt	rt;
	t_rgbf	c;
	t_obj	*nearest;
	double	light_t;

	rt.ray = ray;
	rt.min_t = INFINITY;
	nearest = find_nearest(ctx, ray, &rt.min_t);
	if (nearest)
	{
		if (nearest->mat < 0)
			rt.hit_material = &ctx->default_mat;
		else
			rt.hit_material = &ctx->mat [nearest->mat];
	}
	else
		return ((t_rgbf){0, 0, 0});
	c = rt.hit_material->color;

	rt.hit_point = vec_sum (ray.orig, vec_scale (ray.dir, rt.min_t));
	if (!ctx->lights)
		return (c);
	// FIXME: needs to handle multi lights!
	rt.hit_point = vec_sum (ray.orig, vec_scale (ray.dir, rt.min_t));
	light_t = vec_len(vec_sub(ctx->lights->pos, rt.hit_point));

	// LIGHT OCCLUSION / SHADOW CHECK
	if (find_nearest (ctx, project_ray_from_light (
			*(ctx->lights), rt.hit_point), &light_t) != NULL)
		return (cmul (c, ctx->ambient)); // TODO: clamp ambient in parsing
	rt.hit_normal = get_object_normal (rt.hit_point, nearest);

	// TODO: get_intensity should take array of lights instead of one light
	c = cmul (c, fmin(1.0L, ctx->ambient +
			get_intensity (rt, *(ctx->lights), *rt.hit_material)));
	return (c);
}
