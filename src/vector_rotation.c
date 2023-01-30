/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_rotation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekantane <ekantane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 14:19:38 by ekantane          #+#    #+#             */
/*   Updated: 2023/01/30 15:18:24 by ekantane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

/*
 * Rotation math
*/

static inline t_vec	vec_rotx(double a, t_vec d)
{
	return ((t_vec){
		.x = d.x,
		.y = d.y * cos(a) - d.z * sin(a),
		.z = d.y * sin(a) + d.z * cos(a)
	});
}

static inline t_vec	vec_roty(double a, t_vec d)
{
	return ((t_vec){
		.x = d.x * cos(a) + d.z * sin(a),
		.y = d.y,
		.z = d.z * cos(a) - d.x * sin(a)
	});
}

static inline t_vec	vec_rotz(double a, t_vec d)
{
	return ((t_vec){
		.x = d.x * cos(a) - d.y * sin(a),
		.y = d.x * sin(a) + d.y * cos(a),
		.z = d.z
	});
}

/* Rotate vector d around the world axis by the corresponding
 * angles specified in vector r in degrees (Euler angles)
 *
 * r.x = pitch = nose vertical, or around the RIGHT axis
 * r.y = yaw   = nose horizontal, or around the UP axis
 * r.z = roll  = rotate clockwise, nose pointing in the same direction
*/
t_vec	vec_rot(t_vec dir, t_vec rot)
{
	const double	d2r = M_PI / 180.0;

	return (vec_rotx (d2r * rot.x,
			vec_roty (d2r * rot.y,
				vec_rotz (d2r * rot.z, dir)
			)));
}
