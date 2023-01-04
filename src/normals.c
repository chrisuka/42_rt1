/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekantane <ekantane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 13:02:04 by ikarjala          #+#    #+#             */
/*   Updated: 2023/01/04 18:14:10 by ikarjala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

#if 0
static inline t_vec	cone_normal(t_vec dir, t_vec hit_p, t_obj *obj)
{
	t_vec	n;
	double	m;

	m = vec_dot(dir, obj->rot) * T + vec_dot(vec_sub(RAYSTART, obj->pos), obj->rot);
	n = vec_scale(vec_scale(obj->rot, m), (1 + obj->r * obj->r));
	n = vec_norm(vec_sub(vec_sub(hit_p, obj->pos), n));
	if (vec_dot(dir, n) > 0.0001)
		n = vec_scale(n, -1);
	return (n);
}

{
	t_vec	n;
	double	m;

	m = vec_dot(dir, obj->rot) * T + vec_dot(vec_sub(RAYSTART, obj->pos), obj->rot);
	n = vec_scale(vec_scale(obj->rot, m), (1 + obj->r * obj->r));
	n = vec_norm(vec_sub(vec_sub(hit_p, obj->pos), n));
	if (vec_dot(dir, n) > 0.0001)
		n = vec_scale(n, -1);
	return (n);
}

static inline t_vec	cylinder_normal(t_vec dir, t_vec hit_p, t_obj *obj)
{
	double	m;
	t_vec	n;

	m = vec_dot(dir, obj->rot) * T + vec_dot(vec_sub(RAYSTART, obj->pos), obj->rot);
	n = vec_norm(vec_sub(vec_sub(hit_p, obj->pos), vec_scale(obj->rot, m)));
	if (vec_dot(dir, n) > EPS)
		n = vec_scale(n, -1);
	return (n);
}

	m = vec_dot(dir, obj->rot) * T + vec_dot(vec_sub(RAYSTART, obj->pos), obj->rot);
	p = vec_add(RAYSTART, vec_scale(dir, T));
	n = vec_norm(vec_sub(vec_sub(p, obj->pos), vec_scale(obj->rot, m)));




static inline t_vec	cylinder_normal(t_vec dir, t_vec hit_p, t_obj *obj)
{
	double	m;
	t_vec	n;

	if (vec_dot(hit_p, dir) == 100000)
		return (vec_scale(obj->rot, -1));

	m = vec_dot(vec_sub(hit_p, obj->pos), dir);
	n = vec_sum(obj->pos, vec_scale(dir, m));
	n = vec_norm(vec_sub(hit_p, n));
//	if (vec_dot(dir, n) > EPS)
//		n = vec_scale(n, -1);
	return (n);
}

static inline t_vec	cylinder_normal(t_vec dir, t_vec hit_p, t_obj *obj)
{
	t_vec	n;
	t_vec	x;
	double	m;

	n = vec_sub(hit_p, obj->pos);

	m = vec_dot(n, dir) / vec_dot(dir, dir);
	x = vec_scale(dir, m);
	n = vec_norm(vec_sub(n, x));

	return (n);
}

static inline t_vec	cylinder_normal(t_vec dir, t_vec hit_p, t_obj *obj)
{
	t_vec	n;

	if (vec_dot(hit_p, dir) == 1000000000)
		return (vec_scale(obj->rot, 0));

	n = vec_sub(hit_p, obj->pos);
	n = vec_norm(vec_sub(n, vec_scale(dir, vec_dot(n, dir))));
//	if (vec_dot(dir, n) > EPS)
//		n = vec_scale(n, -1);
	return (n);
}

#endif

/* Return the normal vector of ray intersection point on an sphere's surface.
 * N = Normalize(P - O)
 * where P = ray hit point, O = object origin
*/

static inline t_vec	cone_normal(t_vec dir, t_vec hit_p, t_obj *obj)
{
 	if (vec_dot(hit_p, dir) == 1000000000)
 		return (vec_scale(obj->rot, 0));	// this is a dumb placeholder just to quickly get rid of a prototype error
		
	t_vec n;
	double	distance;

	distance = (hit_p.x * hit_p.x) + (hit_p.z * hit_p.z) + (hit_p.y * hit_p.y);
	if (distance <= 1)
	{
		n.x = 0;
		n.y = 1;
		n.z = 0;
		return (n);
	}
	else
	{
		n.x = hit_p.x,
		n.y = hit_p.y;  // or n.y = 0?
		n.z = hit_p.z;
		return (n);
	}
}

static inline t_vec	cylinder_normal(t_vec dir, t_vec hit_p, t_obj *obj)
{
 	if (vec_dot(hit_p, dir) == 1000000000)
 		return (vec_scale(obj->rot, 0));	// this is a dumb placeholder just to quickly get rid of a prototype error
		
	t_vec n;
	double	distance;

	distance = (hit_p.x * hit_p.x) + (hit_p.z * hit_p.z);
	if (distance <= 1)
	{
		n.x = 0;
		n.y = 1;
		n.z = 0;
		return (n);
	}
	else
	{
		n.x = hit_p.x;
		n.y = 0;
		n.z = hit_p.z;
		return (n);
	}
}

static inline t_vec	plane_normal(t_vec dir, t_vec hit_p, t_obj *obj)
{
	if (vec_dot(dir, obj->rot) < 0)
		return (obj->rot);
	if (vec_dot(hit_p, dir) == 0)
		return (vec_scale(obj->rot, -1));
	return (vec_scale(obj->rot, -1));
}

static inline t_vec	sphere_normal(t_vec dir, t_vec hit_p, t_obj *obj)
{
	t_vec	n;

	n = vec_norm(vec_sub(hit_p, obj->pos));
	if (vec_dot(dir, n) > EPS)
		return (vec_scale (n, -1));
	return (n);
}

t_vec	get_object_normal(t_vec dir, t_vec hit_point, t_obj *obj)
{
	typedef t_vec (*t_nf)(t_vec, t_vec, t_obj *);
	const t_nf	jmp[] = {
		sphere_normal,
		cylinder_normal,
		cone_normal,
		plane_normal
	};

	return (jmp [obj->id](dir, hit_point, obj));
}
