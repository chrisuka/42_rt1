/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikarjala <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 18:53:34 by ikarjala          #+#    #+#             */
/*   Updated: 2023/01/23 15:14:13 by ikarjala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

/* Construct a ray based on the vector parameters.
 * This function is for readability and Norminette's sake.
*/
static inline t_ray	ray_init(t_vec origin, t_vec direction)
{
	return ((t_ray){
		.orig = origin,
		.dir = direction});
}

/*
 * Specular (Phong model): we multiply the object's specular factor with
 * a factor raised to the power of the object's shininess value.
 * We get this factor as cosine of the angle between Vr and L
 *
 * L = direction from object to light source (*light_rdir*)
 * Vr = reflection of Viewport vector (*reflection*)
 * 0 = ( |Vr| . |L| ) / ( ||Vr|| * ||L|| )
 * cos0 = |Vr| . |L|
*/
static inline double	get_specular_hi(t_rt rt, double base_intensity,
		t_vec light_rdir, t_mat m)
{
	const t_vec		reflection = vec_reflect (light_rdir, rt.hit_normal);
	const double	dot = vec_dot (reflection, vec_scale (rt.ray.dir, -1));

	if (dot > EPS)
		return (0);
	return (base_intensity * m.specular * pow(dot, m.gloss));
}

/* Calculate the summed intensity of all the light sources in the scene
 * and return a multiplier for how bright the intersection point on an
 * object's surface should be.
 *
 * Ambient: base intensity
 *
 * Diffuse: every light source outputs I (ray width) amount of
 * energy spread evenly over area A, i = I / A
 * Area is from 1 to infinity based on the angle between vL and vN.
 *
 * Use Dot Product to get the cosine of the angle to use as multiplier [0-1].
 * vL = P - Q  (light vector = hit point - light origin)
 * vN = hit normal
 * (I/A = 1) when (vL . vN = 0) aka vL is perpendicular to surface
 * lim A->inf I/A = 0
 *   angle < 0: the light is coming from behind the surface.
 *   angle = 0: the light would spread over infinite A.
 * In either case it would contribute no light to the surface,
 * therefore we only apply it if the angle is greater than Epsilon.
 *
 * Falloff: Due to the same spread, the light's impact drops
 * exponentially the further away it is: i *= 1 / dst^2
*/
double	get_intensity(t_rt rt, t_light *lights, size_t lcount, t_mat m)
{
	t_vec	light_rdir;
	double	light_t;
	double	angle_mul;
	double	falloff;
	double	intensity;

	intensity = 0.0L;
	while (lcount --)
	{
		light_rdir = vec_sub (lights[lcount].pos, rt.hit_point);
		light_t = vec_dot (light_rdir, light_rdir);
		falloff = lights[lcount].intensity / light_t;
		light_t = sqrt (light_t);
		light_rdir = vec_scale (light_rdir, 1.0 / light_t);
		// OCCLUSION / SHADOW CHECK
		if (find_nearest (rt.ctx, ray_init (
					rt.hit_point, light_rdir), &light_t) != NULL)
			continue ;
		// ========================
		angle_mul = vec_dot (light_rdir, rt.hit_normal);
		if (angle_mul > EPS)
			intensity += falloff * angle_mul;
		if (m.specular > 0)
			intensity += get_specular_hi (rt, falloff, light_rdir, m);
	}
	return (intensity);
}
