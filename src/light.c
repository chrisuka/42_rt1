/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikarjala <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 18:53:34 by ikarjala          #+#    #+#             */
/*   Updated: 2022/11/30 15:31:35 by ikarjala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

/* Calculate the summed intensity of all the light sources in the scene
 * and return a multiplier for how bright the intersection point on an
 * object's surface should be.
 *
 * Diffuse shading: every light source outputs I (ray width) amount of
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
double	get_intensity(t_vec hit_p, t_vec hit_n, t_light light)
{
	// NOTE: light_dir is currently from obj towards light
	const t_vec		light_dir = vec_norm (vec_sub (light.pos, hit_p));
	const double	angle = vec_dot (light_dir, hit_n);
	double			intensity;

	intensity = 0.0L;
	
	// NOTE: for every light...

	if (angle > EPS)
		intensity += light.intensity *
			(angle / (vec_len(light_dir) * vec_len(hit_n)));

	// NOTE: what the heck?! we are dividing by
	// the product of the lengths of 2 unit vectors? WHY?!
	// won't this always result in 1 ?!
	// x/(|vA| * |vB|) = x/1*1 = x/1 = x
	
#if 0 // WIP
	if (obj.specular > 0)
		intensity += fpow(cos(vec_dot (CAM_vZ, L_vREFLECTION)), obj.specular);
#endif
	return (intensity);
}

// TODO: more accurate name for this function
// i.e.  get_light_mul
//       get_brightness

// TODO: add explanation for cos(alpha) in I/A
