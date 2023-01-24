/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekantane <ekantane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 11:36:51 by ikarjala          #+#    #+#             */
/*   Updated: 2023/01/24 17:10:30 by ekantane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

/* PREFACE:
 * The basic idea of all the ray-primitive intersections is that we can
 * form a triangle from the vectors of the ray, the object position and
 * ray origin, and we can form a quadratic function to determine the scalar t.
 *
 * For every generic point P on a surface, it needs to satisfy an equation
 * depending on the properties of the shape. We check whether tR satisfies
 * this equation by finding the 0-roots in the quadratic equation.
 *
 * The roots tell us what kind of intersection it was and t represents the
 * distance from the ray origin to the intersection point. We can get the
 * intersection position in Cartesian coordinates by R0 + tR where
 * R0 = ray origin, R = ray direction.
*/

/* Solve quadratic function and return the more ideal solution to get
 * the closest real intersection t, or -1 if there are no real roots.
 *
 * D = discriminant
 * D = b*b - 4ac
 *   D > 0: there are two intersections.
 *   D = 0: there is one intersection.
 *   D < 0: there are no intersections.
 *
 * t will be used as a scalar representing the distance
 * from ray origin to the closest intersection point.
*/

static double	select_root(double a, double b, double c)
{
	const double	d = b * b - 4 * a * c;
	double			d_root;
	double			aa_inv;
	double			t1;
	double			t2;

	if (d < 0)
		return (-1);
	aa_inv = 1 / (2 * a);
	d_root = sqrt(d);
	t1 = (-b - d_root) * aa_inv;
	t2 = (-b + d_root) * aa_inv;
	if ((t1 <= t2 && t1 >= 0) || (t1 >= 0 && t2 < 0))
		return (t1);
	else if ((t2 <= t1 && t2 >= 0) || (t1 < 0 && t2 >= 0))
		return (t2);
	return (-1);
}

/*
PLANE:
t = -(point on the line - plane center) * rotation) / (line direction * rotation)

*/

static inline double	intersect_plane(t_ray ray, t_obj obj)
{
	double	a;
	double	b;
	double	t;

	a = vec_dot(vec_sub(ray.orig, obj.pos), obj.rot);
	b = vec_dot(ray.dir, obj.rot);
	t = -a / b;
	if (b == 0 || (a < 0 && b < 0) || (a > 0 && b > 0) || t <= EPS)
		return (-1);
	return (t);
}

/* CONE:
 * r = base radius
 * C = base center position
 * H = cone peak position, C + height
 * Q = nearest point on h from (L0 + tv)
 *
 * m = constant representing ratio of r / ||H - C||
 *   = r^2 / (||H - C|| . ||H - C||)
 * 
 * Generic point P on the surface:
 * P . Q = m((P - H) . h)^2
 *
 * TODO: figure out if m is just an angle for how steep the cone is
 * TODO: clean this up and fix the math! This is not acceptable!
*/
static inline double	intersect_cone(t_ray ray, t_obj obj)
{
	t_vec	oc;
	double	a;
	double	b;
	double	c;
	double	m;
	double	n;
	double	o;

	obj.rot = vec_norm (obj.rot);
	oc = vec_sub(ray.orig, obj.pos);
	m = obj.r * obj.r;
	n = vec_dot(ray.dir, obj.rot);
	o = vec_dot(oc, obj.rot);
	a = vec_dot(ray.dir, ray.dir) - m * pow(n, 2) - pow(n, 2);
	b = 2 * ((vec_dot(ray.dir, oc) - (m * n) * o - n * o));
	c = vec_dot(oc, oc) - (m * pow(o, 2)) - pow(o, 2);
	return (select_root (a, b, c));
}

/* CYLINDER
 * Generic point P on the surface:
 * ||P - Q|| = r , equivalent to
 * (P - Q) . (P - Q) = r^2
 * oc = object center
*/
static inline double	intersect_cylinder(t_ray ray, t_obj obj)
{
	t_vec	oc;
	double	a;
	double	b;
	double	c;
	double	n;
	double	o;

	obj.rot = vec_norm(obj.rot); // TODO: remove unnecessary normalization
	oc = vec_sub(ray.orig, obj.pos);
	n = vec_dot(ray.dir, obj.rot);
	o = vec_dot(oc, obj.rot);
	a = vec_dot(ray.dir, ray.dir) - pow(n, 2);
	b = 2 * (vec_dot(ray.dir, oc) - (n * o));
	c = vec_dot(oc, oc) - pow(o, 2) - pow(obj.r, 2);
	return (select_root (a, b, c));
}

/* SPHERE:
 * Generic point P on the surface:
 * ||P - O|| = r
 *
 * x = R0 - C
 * a = sqr magnitude of R
 * b = ??
 * c = ??
*/
static inline double	intersect_sphere(t_ray ray, t_obj obj)
{
	t_vec	oc;
	double	a;
	double	b;
	double	c;

	oc = vec_sub(ray.orig, obj.pos);
	a = vec_dot(ray.dir, ray.dir);
	b = 2 * vec_dot(oc, ray.dir);
	c = vec_dot(oc, oc) - (obj.r * obj.r);
	return (select_root (a, b, c));
}

double	intersect(t_ray ray, t_obj obj)
{
	typedef double (*t_rayfn)(t_ray, t_obj);
	const t_rayfn	jmp[] = {
		intersect_sphere,
		intersect_cylinder,
		intersect_cone,
		intersect_plane
	};

	obj.rot = vec_norm(obj.rot); //TODO: this should not be necessary! normalize during parsing!
	return (jmp [obj.id](ray, obj));
}
