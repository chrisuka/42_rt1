/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikarjala <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 18:53:34 by ikarjala          #+#    #+#             */
/*   Updated: 2023/01/13 19:01:22 by ikarjala         ###   ########.fr       */
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
double	get_intensity(t_vec Vz, t_vec hit_p, t_vec hit_n, t_light light, t_obj *obj)
{
	const t_mat		m = (t_mat)(*obj->mat);
	const t_vec		light_dir = vec_norm (vec_sub (light.pos, hit_p));
	const double	angle = vec_dot (light_dir, hit_n);
	double			intensity;

	//const double	matte = (1.0L - obj->gloss);
	intensity = 0.0L;
	
	// NOTE: for every light...

	if (angle > EPS)
		intensity += light.intensity * angle;

#if 1 // WIP
	const t_vec Vr = vec_reflect (Vz, hit_n);
	if (m.specular > 0) //&& obj->gloss > 0
		intensity += light.intensity * m.specular * 
			pow(vec_dot (Vr, light_dir), m.gloss);
#endif
	return (intensity);
}

// TODO: more accurate name for this function
// i.e.  get_light_mul
//       get_brightness
