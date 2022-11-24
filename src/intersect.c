/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikarjala <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 11:36:51 by ikarjala          #+#    #+#             */
/*   Updated: 2022/11/24 14:18:43 by ikarjala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static double	get_t(double a, double b, double d)
{
	const double	root = sqrt(d);
	double			t1;
	double			t2;

	t1 = (-b - root) / (2 * a);
	t2 = (-b + root) / (2 * a);
	if ((t1 <= t2 && t1 >= 0) || (t1 >= 0 && t2 < 0))
		return (t1);
	else if ((t2 <= t1 && t2 >= 0) || (t1 < 0 && t2 >= 0))
		return (t2);
	return (-1);
}

static inline double	intersect_sphere(t_ray ray, t_obj obj)
{
	double	a;
	double	b;
	double	c;
	double	d;
	t_vec	oc;

	oc = vec_sub(o, obj->pos);
	a = vec_dot(dir, dir);
	b = 2 * vec_dot(oc, dir);
	c = vec_dot(oc, oc) - (obj->r * obj->r);
	d = b * b - 4 * a * c;
	if (d < 0)
		return (-1);
	return (get_t(a, b, d));
}

double	intersect(t_ray ray, t_obj obj)
{
	const double	(*fn[])(t_ray, t_obj) = {
		&intersect_sphere
			,
		//&intersect_cylinder,
		//&intersect_cone,
		//&intersect_plane
	};

	return (fn[0](ray, obj));
}
