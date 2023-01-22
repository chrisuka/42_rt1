/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikarjala <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 18:53:34 by ikarjala          #+#    #+#             */
/*   Updated: 2023/01/22 19:39:23 by ikarjala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

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
 * vL = P - Q  (light vector = hit point - light origin)
 * vN = hit normal
 * (I/A = 1) when (vL . vN = 0) aka vL is perpendicular to surface
 * lim A->inf I/A = 0
 * 
 * If the angle < 0, the light is coming from behind the surface.
 * If the angle = 0, the light would spread over A infinity.
 * In either case it would contribute no light to the surface,
 * therefore we only apply it if the angle is greater than Epsilon.
*/
double	get_intensity(t_rt rt, t_light *lights, size_t lcount, t_mat m)
{
	t_vec	light_rdir;
	double	light_t;
	double	angle;
	double	falloff;
	double	intensity;

	intensity = 0.0L;
	while (lcount --)
	{
		light_rdir = vec_sub (lights[lcount].pos, rt.hit_point);
		light_t = vec_len (light_rdir);
		falloff = lights[lcount].intensity / light_t;
		light_rdir = vec_scale (light_rdir, 1.0 / light_t);
		// OCCLUSION / SHADOW CHECK
		if (find_nearest (rt.ctx, project_ray_from_light (
				lights[lcount], rt.hit_point), &light_t) != NULL)
			continue ;
		// ========================
		angle = vec_dot (light_rdir, rt.hit_normal);
		if (angle > EPS)
			intensity += falloff * angle;
		if (m.specular > 0)
			intensity += get_specular_hi (rt, falloff, light_rdir, m);
	}
	return (intensity);
}
