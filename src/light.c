/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikarjala <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 18:53:34 by ikarjala          #+#    #+#             */
/*   Updated: 2023/01/20 14:01:07 by ikarjala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

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
 *
 * Specular (Phong model): we multiply the object's specular factor with
 * a factor raised to the power of the object's shininess value.
 * We get this factor as cosine of the angle between Vr and L
 *
 * L = direction from object to light source
 * Vr = reflection of Viewport vector
 * 0 = ( |Vr| . |L| ) / ( ||Vr|| * ||L|| )
 * cos0 = |Vr| . |L|
*/
double	get_intensity(t_rt rt, t_light light, t_mat m)
{
	const t_vec		light_vec = vec_sub (light.pos, rt.hit_point);
	const t_vec		light_dir = vec_norm (light_vec);
	const double	angle = vec_dot (light_dir, rt.hit_normal);
	double			intensity;

	//const double	matte = (1.0L - mat.gloss);
	intensity = 0.0L;
	
	// NOTE: for every light...

	if (angle > EPS)
		intensity += light.intensity * angle;

	const t_vec Lr = vec_reflect (light_dir, rt.hit_normal);
	const double dot = vec_dot (Lr, vec_scale (rt.ray.dir, -1));

	if (m.specular > 0 && dot < 0)
		intensity += light.intensity * m.specular * 
			pow(dot, m.gloss);
	return (intensity);
}

// TODO: more accurate name for this function
// i.e.  get_light_mul
//       get_brightness
