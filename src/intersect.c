/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekantane <ekantane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 11:36:51 by ikarjala          #+#    #+#             */
/*   Updated: 2023/01/09 13:58:08 by ekantane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

/* PREFACE:
 * The basic idea of all the ray-primitive intersections is that we can
 * form a triangle from the vectors of the ray, the object position and
 * ray origin, and we can form a quadratic function to determine the scalar t.
 * The roots tell us what kind of intersection it was and t represents the
 * distance from the ray origin to the intersection point. We can get the
 * intersection position in Cartesian coordinates by R0 + t(R) where
 * R0 = ray origin, R = ray direction.
*/

/* Solve quadratic function and return the more ideal solution to get
 * the closest real intersection t, or -1 if there are no real roots.
*/
static inline double	select_root(double a, double b, double d)
{
	const double	aa_inv = 1 / (2 * a);
	const double	disc_root = sqrt(d);
	const double	t1 = (-b - disc_root) * aa_inv;
	const double	t2 = (-b + disc_root) * aa_inv;

	if ((t1 <= t2 && t1 >= 0) || (t1 >= 0 && t2 < 0))
		return (t1);
	else if ((t2 <= t1 && t2 >= 0) || (t1 < 0 && t2 >= 0))
		return (t2);
	return (-1);
}

/*

SPHERE:
a =  squared magnitude of ray direction
b = 2 * (line direction * (point on the line * sphere center))
c = (square of (point on the line * sphere center)) - square of radius

D = b*b - 4ac
if	D > 0	there are two intersections
if	D = 0	there is one intersection
if	D < 0	there are no intersections

The equations in select_root handling the discriminant tell the locations of the intersections.

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

static inline double	intersect_cone(t_ray ray, t_obj obj)
{
	double	a;
	double	b;
	double	c;
	double	d;
	t_vec	x;
	double	m;

	obj.rot = vec_norm(obj.rot);
	m = pow(obj.r, 2) + 1;								// this is a bit iffy
	x = vec_sub(ray.orig, obj.pos);
	a = vec_dot(ray.dir, ray.dir) - m * pow(vec_dot(ray.dir, obj.rot), 2) - pow(vec_dot(ray.dir, obj.rot), 2);
	b = 2 * ((vec_dot(ray.dir, x) - (m * vec_dot(ray.dir, obj.rot)) * vec_dot(x, obj.rot) - vec_dot(ray.dir, obj.rot) * vec_dot(x, obj.rot)));
	c = vec_dot(x, x) - (m * pow(vec_dot(x, obj.rot), 2)) - pow(vec_dot(x, obj.rot), 2);
	d = b * b - 4 * a * c;
	if (d < 0)
		return (-1);
	return (select_root (a, b, d));
}
/*
	t_vec	x;
	double	a;
	double	b;
	double	c;
	double	d;

	x = vec_sub(ray.orig, obj.pos);
	a = vec_dot(ray.dir, obj.rot);
	a = vec_dot(ray.dir, ray.dir) - a * a;
	b = 2 * (vec_dot(ray.dir, x) - vec_dot(ray.dir, obj.rot)
		* vec_dot(x, obj.rot));
	c = vec_dot(x, obj.rot);
	c = vec_dot(x, x) - c * c - obj.r * obj.r;
	d = b * b - 4 * a * c;
	d = DROUND(d);
	return (d = d < 0 ? -1 : select_root(a, b, d));
*/

static inline double	intersect_cylinder(t_ray ray, t_obj obj)
{
	double	a;
	double	b;
	double	c;
	double	d;
	t_vec	x;

	obj.rot = vec_norm(obj.rot);
	x = vec_sub(ray.orig, obj.pos);
	a = vec_dot(ray.dir, ray.dir) - pow(vec_dot(ray.dir, obj.rot), 2);
	b = 2 * (vec_dot(ray.dir, x) - (vec_dot(ray.dir, obj.rot) * vec_dot(x, obj.rot)));
	c = vec_dot(x, x) - pow(vec_dot(x, obj.rot), 2) - pow(obj.r, 2);
	d = b * b - 4 * a * c;
	if (d < 0)
		return (-1);
	return (select_root (a, b, d));
}

static inline double	intersect_sphere(t_ray ray, t_obj obj)
{
	double	a;
	double	b;
	double	c;
	double	d;
	t_vec	oc;

	oc = vec_sub(ray.orig, obj.pos);
	a = vec_dot(ray.dir, ray.dir);
	b = 2 * vec_dot(oc, ray.dir);
	c = vec_dot(oc, oc) - (obj.r * obj.r);
	d = b * b - 4 * a * c; // discriminant
	if (d < 0)
		return (-1);
	return (select_root (a, b, d));
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
	t_rt	rt;

	rt.t = intersect_cylinder(ray, obj);
	obj.rot = vec_norm(obj.rot);
	return (jmp [obj.id](ray, obj));
}
