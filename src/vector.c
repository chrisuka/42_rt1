/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekantane <ekantane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 14:19:38 by ekantane          #+#    #+#             */
/*   Updated: 2023/01/14 18:05:35 by ikarjala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

/* Return the Dot product between vectors v1 and v2
 * (scalar gotten by adding together the products of the individual axis).
*/
double	vec_dot(t_vec v1, t_vec v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

/* Return length (magnitude) of vector v1.
*/
double	vec_len(t_vec v1)
{
	return (sqrt(vec_dot(v1, v1)));
}

/* Normalize, or return a unit vector (magnitude scaled to 1) of v1.
*/
t_vec	vec_norm(t_vec v1)
{
	double	inv;

	inv = 1 / vec_len(v1);
	return (vec_scale(v1, inv));
}

/* Return vector d, reflected by normal vector n
 * r = d - 2(d . n)n
*/
t_vec	vec_reflect(t_vec d, t_vec n)
{
	return (vec_sub (d, vec_scale (n, 2 * vec_dot(d, n))));
}

t_vec	vec_scale(t_vec v1, double t)
{
	v1.x *= t;
	v1.y *= t;
	v1.z *= t;
	return (v1);
}

t_vec	vec_sum(t_vec v1, t_vec v2)
{
	v1.x += v2.x;
	v1.y += v2.y;
	v1.z += v2.z;
	return (v1);
}

t_vec	vec_sub(t_vec v1, t_vec v2)
{
	v1.x -= v2.x;
	v1.y -= v2.y;
	v1.z -= v2.z;
	return (v1);
}

/*
 * Rotation math
*/

/* Rotate vector d around the world axis by the corresponding
 * angles specified in vector r in degrees (Euler angles)
 *
 * r.x = pitch = nose vertical, or around the RIGHT axis
 * r.y = yaw   = nose horizontal, or around the UP axis
 * r.z = roll  = rotate clockwise, nose pointing in the same direction
*/
t_vec	vec_rot(t_vec d, t_vec r)
{
	d = vec_rotx(d, DTR(r.x));
	d = vec_roty(d, DTR(r.y));
	d = vec_rotz(d, DTR(r.z));
	return (d);
}

t_vec	vec_rotx(t_vec d, double a)
{
	t_vec r;

	r.x = d.x;
	r.y = d.y * cos(a) - d.z * sin(a);
	r.z = d.y * sin(a) + d.z * cos(a);
	return (r);
}

t_vec	vec_roty(t_vec d, double a)
{
	t_vec r;

	r.x = d.x * cos(a) + d.z * sin(a);
	r.y = d.y;
	r.z = d.z * cos(a) - d.x * sin(a);
	return (r);
}

t_vec	vec_rotz(t_vec d, double a)
{
	t_vec	r;

	r.x = d.x * cos(a) - d.y * sin(a);
	r.y = d.x * sin(a) + d.y * cos(a);
	r.z = d.z;
	return (r);
}

/* Return the cross prduct of two vectors.
*/
t_vec vec_cross(t_vec u, t_vec v)
{
	t_vec	r;

	r.x = u.y * v.z - u.z * v.y;
	r.y = u.z * v.x - u.x * v.z;
	r.z = u.x * v.y - u.y * v.x;
	return (r);
}
