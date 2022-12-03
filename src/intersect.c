/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekantane <ekantane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 11:36:51 by ikarjala          #+#    #+#             */
/*   Updated: 2022/12/03 17:14:04 by ekantane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

/* Solve quadratic function and return the more ideal solution to get
 * the closer intersection, or -1 for invalid / unexpected results.
*/
static inline double	choose_quad_result(double a, double b, double d)
{
	double	t1;
	double	t2;

	t1 = (-b - sqrt(d)) / (2 * a);
	t2 = (-b + sqrt(d)) / (2 * a);
	if ((t1 <= t2 && t1 >= 0) || (t1 >= 0 && t2 < 0))
		return (t1);
	else if ((t2 <= t1 && t2 >= 0) || (t1 < 0 && t2 >= 0))
		return (t2);
	return (-1);
}

/*

SPHERE:
a =  square of line direction
b = 2 * (line direction * (point on the line * sphere center))
c = (square of (point on the line * sphere center)) - square of radius

if	b * b - 4 * a * c > 0	there are two intersections
if	b * b - 4 * a * c = 0	there is one intersection
if	b * b - 4 * a * c < 0	there are no intersections

The equations in choose_quad_result handling the discriminant tell the locations of the intersections.

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
	return (choose_quad_result (a, b, d));
}

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
	return (choose_quad_result (a, b, d));
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
	return (choose_quad_result (a, b, d));
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

	return (jmp [obj.id](ray, obj));
}
