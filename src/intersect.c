/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekantane <ekantane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 11:36:51 by ikarjala          #+#    #+#             */
/*   Updated: 2023/01/23 15:42:36 by ikarjala         ###   ########.fr       */
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
 * D = discriminant
 *   D > 0: there are two intersections.
 *   D = 0: there is one intersection.
 *   D < 0: there are no intersections.
 *
 * t will be used as a scalar representing the distance
 * from ray origin to the closest intersection point.
*/

static double	select_root(double a, double b, double d)
{
	double	aa_inv;
	double	disc_root;
	double	t1;
	double	t2;

	if (d < 0)
		return (-1);
	aa_inv = 1 / (2 * a);
	disc_root = sqrt(d);
	t1 = (-b - disc_root) * aa_inv;
	t2 = (-b + disc_root) * aa_inv;
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
 * m = constant representing ratio of ||r|| to ||H - C||
 * 
 * Generic point P on the surface:
 * P . Q = m((P - H) . h)^2
 *
 * TODO: clean this up and fix the math! This is not accurate!
*/
static inline double	intersect_cone(t_ray ray, t_obj obj)
{
	double	a;
	double	b;
	double	c;
	double	d;
	t_vec	x;
	double	m;

	obj.rot = vec_norm (obj.rot);
	m = obj.r * obj.r;
	x = vec_sub(ray.orig, obj.pos);
	a = vec_dot(ray.dir, ray.dir) - m * pow(vec_dot(ray.dir, obj.rot), 2) - pow(vec_dot(ray.dir, obj.rot), 2);
	b = 2 * ((vec_dot(ray.dir, x) - (m * vec_dot(ray.dir, obj.rot)) * vec_dot(x, obj.rot) - vec_dot(ray.dir, obj.rot) * vec_dot(x, obj.rot)));
	c = vec_dot(x, x) - (m * pow(vec_dot(x, obj.rot), 2)) - pow(vec_dot(x, obj.rot), 2);
	d = b * b - 4 * a * c;
	return (select_root (a, b, d));
}

/* CYLINDER
 * Generic point P on the surface:
 * ||P - Q|| = r , equivalent to
 * (P - Q) . (P - Q) = r^2
 *
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
	return (select_root (a, b, d));
}

/* SPHERE:
 * Generic point P on the surface:
 * ||P - O|| = r
 *
 * a =  squared magnitude of *ray*
 * b = 2 * (line direction * (point on the line * sphere center))
 * c = (square of (point on the line * sphere center)) - square of radius
 *
 * D = b*b - 4ac
*/
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
	d = b * b - 4 * a * c;
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

	obj.rot = vec_norm(obj.rot); //TODO: this should not be necessary! normalize during parsing!
	return (jmp [obj.id](ray, obj));
}
