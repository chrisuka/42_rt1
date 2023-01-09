/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekantane <ekantane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 13:02:04 by ikarjala          #+#    #+#             */
/*   Updated: 2023/01/09 13:54:44 by ekantane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

/* Return the normal vector of ray intersection point on an sphere's surface.
 * N = Normalize(P - O)
 * where P = ray hit point, O = object origin
*/

static inline t_vec	cone_normal(t_vec dir, t_vec hit_p, t_obj *obj, t_vec raystart)
{
	if (vec_dot(hit_p, raystart) == 1000000000)
 		return (vec_scale(obj->rot, 0));	// this is a dumb placeholder just to quickly get rid of a prototype error
	
	t_vec	n;
	t_vec	hypotenuse;

	hypotenuse = vec_sub(hit_p, obj->pos);
	n = vec_norm(vec_cross(hypotenuse, vec_cross(hypotenuse, obj->rot)));
	if (vec_dot(dir, n) > EPS)
		n = vec_scale(n, -1);
	return (n);
}

static inline t_vec	cylinder_normal(t_vec dir, t_vec hit_p, t_obj *obj, t_vec raystart)
{
	if (vec_dot(dir, raystart) == 1000000000)
 		return (vec_scale(obj->rot, 0));	// this is a dumb placeholder just to quickly get rid of a prototype error
		
	t_vec	hypotenuse;
	t_vec	h_hitp; // closest point along h vector
	t_vec	normal;
	double	h_scalar;

	hypotenuse = vec_sub (hit_p, obj->pos);
	h_scalar = vec_dot (hypotenuse, obj->rot);
	h_hitp = vec_sum (obj->pos, vec_scale (obj->rot, h_scalar));
	normal = vec_norm (vec_sub (hit_p, h_hitp));
	return (normal);
}

static inline t_vec	plane_normal(t_vec dir, t_vec hit_p, t_obj *obj, t_vec raystart)
{
	if (vec_dot(raystart, dir) == 1000000000)
 		return (vec_scale(obj->rot, 0));	// this is a dumb placeholder just to quickly get rid of a prototype error

	if (vec_dot(dir, obj->rot) < 0)
		return (obj->rot);
	if (vec_dot(hit_p, dir) == 0)
		return (vec_scale(obj->rot, -1));
	return (vec_scale(obj->rot, -1));
}

static inline t_vec	sphere_normal(t_vec dir, t_vec hit_p, t_obj *obj, t_vec raystart)
{
 	if (vec_dot(raystart, dir) == 1000000000)
 		return (vec_scale(obj->rot, 0));	// this is a dumb placeholder just to quickly get rid of a prototype error
		
	t_vec	n;

	n = vec_norm(vec_sub(hit_p, obj->pos));
	if (vec_dot(dir, n) > EPS)
		return (vec_scale (n, -1));
	return (n);
}

t_vec	get_object_normal(t_vec dir, t_vec hit_point, t_obj *obj, t_vec raystart)
{
	typedef t_vec (*t_nf)(t_vec, t_vec, t_obj *, t_vec);
	const t_nf	jmp[] = {
		sphere_normal,
		cylinder_normal,
		cone_normal,
		plane_normal
	};
	return (jmp [obj->id](dir, hit_point, obj, raystart));
}
