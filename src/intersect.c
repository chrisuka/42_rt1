/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekantane <ekantane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 11:36:51 by ikarjala          #+#    #+#             */
/*   Updated: 2022/11/30 14:37:09 by ikarjala         ###   ########.fr       */
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

#if 0
static inline double	intersect_plane(t_vec dir, t_object *obj)
{
	double	a;
	double	b;
	double	t;
	
	a = vec_dot(vec_sub(ray.orig, obj->pos), obj->rot);
	b = vec_dot(dir, obj->rot);
	t = -a / b;
	if (b == 0 || (a < 0 && b < 0) || (a > 0 && b > 0) || t <= EPS)
		return (-1);
	return (t);
}

static inline double	intersect_cone(t_vec dir, t_object *obj)
{
	double	a;
	double	b;
	double	c;
	double	d;
	t_vec	x;
	double	m;

	m = pow(obj->r, 2);
	x = vec_sub(ray.orig, obj->pos);
	
	a = vec_dot(dir, dir) - m * pow(vec_dot(dir, obj->rot), 2) -
		pow(vec_dot(dir, obj->rot), 2);
	b = 2 * ((vec_dot(dir, x) - (m * vec_dot(dir, obj->rot)) *
		vec_dot(x, obj->rot) - vec_dot(dir, obj->rot) * vec_dot(x, obj->rot)));
		pow(vec_dot(x, obj->rot), 2);
	d = b * b - 4 * a * c;
	if (d < 0)
		return (-1);
	return (choose_quad_result (a, b, d));
}

static inline double	intersect_cylinder(t_vec dir, t_object *obj)
{
	double	a;
	double	b;
	double	c;
	double	d;
	t_vec	x;

	x = vec_sub(ray.orig, obj->pos);
	a = vec_dot(dir, dir) - pow(vec_dot(dir, obj->rot), 2);
	b = 2 * (vec_dot(dir, x) - (vec_dot(dir, obj->rot) * vec_dot(x, obj->rot)));
	c = vec_dot(x, x) - pow(vec_dot(x, obj->rot), 2) - pow(obj->r, 2);
	d = b * b - 4 * a * c;
	if (d < 0)
		return (-1);
	return (choose_quad_result (a, b, d));
}
#endif

static inline double	intersect_sphere(t_ray ray, t_object obj)
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

double	intersect(t_ray ray, t_object obj)
{
	typedef double (*t_rayfn)(t_ray, t_object);
	const t_rayfn	jmp[] = {
		intersect_sphere
		//intersect_cylinder,
		//intersect_cone,
		//intersect_plane
	};

	return (jmp [obj.id](ray, obj));
}
