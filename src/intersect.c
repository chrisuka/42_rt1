/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekantane <ekantane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 11:36:51 by ikarjala          #+#    #+#             */
/*   Updated: 2023/01/31 19:53:11 by ikarjala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

/* PREFACE:
 * The basic idea of all the ray-primitive intersections is that each shape
 * has a certain geometric definition and from its properties we can get
 * coefficients to form a quadratic equation to determine the scalar t.
 *
 * For every generic point P on a surface, it needs to satisfy an equation
 * depending on the properties of the shape. We check whether tR satisfies
 * this equation by solving the 0-roots in the quadratic equation.
 *
 * The roots represent the intersection points through the shape, there can be
 * 0, 1 or 2.
 * distance from the ray origin to the intersection point. We can get the
 * intersection position in Cartesian coordinates by R0 + tR where
 * R0 = ray origin, R = ray direction.
*/

/*
 * PLANE:
 * C = plane center
 * N = plane normal vector
 *
 * Generic point P on the surface:
 * (P - C) . N = 0
 *
 *  q.b == 0: ray is tangental to plane surface
 *  q.b  > 0: ray is from behind plane's "facing" side
*/
static inline double	intersect_plane(t_ray ray, t_obj obj)
{
	t_quad	q;
	double	t;

	q.a = vec_dot(vec_sub(ray.orig, obj.pos), obj.rot);
	q.b = vec_dot(ray.dir, obj.rot);
	t = -q.a / q.b;
	if (q.b >= 0 || (q.a < 0 && q.b < 0) || (q.a > 0 && q.b > 0) || t <= EPS)
		return (-1);
	return (t);
}

/* CONE:
 * r = base radius
 * C = base center position
 * H = cone peak position, C + height
 * Q = nearest point on h from (L0 + tv)
 * m = constant representing ratio of r / ||H - C||
 *   = r^2 / (||H - C|| . ||H - C||)
 * 
 * Generic point P on the surface:
 * P . Q = m((P - H) . h)^2
*/
static inline double	intersect_cone(t_ray ray, t_obj obj)
{
	t_quad	q;
	t_vec	oc;
	double	m;
	double	n;
	double	o;

	oc = vec_sub(ray.orig, obj.pos);
	m = obj.r * obj.r;
	n = vec_dot(ray.dir, obj.rot);
	o = vec_dot(oc, obj.rot);
	q.a = vec_dot(ray.dir, ray.dir) - m * pow(n, 2) - pow(n, 2);
	q.b = 2 * ((vec_dot(ray.dir, oc) - (m * n) * o - n * o));
	q.c = vec_dot(oc, oc) - (m * pow(o, 2)) - pow(o, 2);
	return (solve (q.a, q.b, q.c));
}

/* CYLINDER
 * Generic point P on the surface:
 * ||P - Q|| = r
*/
static inline double	intersect_cylinder(t_ray ray, t_obj obj)
{
	t_quad	q;
	t_vec	oc;
	double	n;
	double	o;

	oc = vec_sub(ray.orig, obj.pos);
	n = vec_dot(ray.dir, obj.rot);
	o = vec_dot(oc, obj.rot);
	q.a = vec_dot(ray.dir, ray.dir) - pow(n, 2);
	q.b = 2 * (vec_dot(ray.dir, oc) - (n * o));
	q.c = vec_dot(oc, oc) - pow(o, 2) - pow(obj.r, 2);
	return (solve (q.a, q.b, q.c));
}

/* SPHERE:
 * Generic point P on the surface:
 * ||P - O|| = r
*/
static inline double	intersect_sphere(t_ray ray, t_obj obj)
{
	t_quad	q;
	t_vec	oc;

	oc = vec_sub (ray.orig, obj.pos);
	q.a = vec_dot (ray.dir, ray.dir);
	q.b = 2 * vec_dot (oc, ray.dir);
	q.c = vec_dot (oc, oc) - (obj.r * obj.r);
	return (solve (q.a, q.b, q.c));
}

double	intersect(t_ray ray, t_obj obj)
{
	const t_rayfn	jmp[] = {
		intersect_sphere,
		intersect_cylinder,
		intersect_cone,
		intersect_plane
	};

	return (jmp [obj.id](ray, obj));
}
