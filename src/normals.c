/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekantane <ekantane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 13:02:04 by ikarjala          #+#    #+#             */
/*   Updated: 2023/01/20 15:00:19 by ikarjala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static inline t_vec	plane_normal(t_vec hit_p, t_obj *obj)
{
	(void)(hit_p);
	return (obj->rot);
}

static inline t_vec	cone_normal(t_vec hit_p, t_obj *obj)
{
	t_vec	n;
	t_vec	hypotenuse;

	hypotenuse = vec_sub(hit_p, obj->pos);
	n = vec_norm(vec_cross(hypotenuse, vec_cross(hypotenuse, obj->rot)));
	if (hit_p.y < obj->pos.y)
		return (vec_scale (n, -1));
	return (n);
}

static inline t_vec	cylinder_normal(t_vec hit_p, t_obj *obj)
{
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

/* Return the normal vector of ray intersection point on an sphere's surface.
 * N = Normalize(P - O)
 * where P = ray hit point, O = object origin
*/

static inline t_vec	sphere_normal(t_vec hit_p, t_obj *obj)
{
	return (vec_norm (vec_sub (hit_p, obj->pos)));
}

t_vec	get_object_normal(t_vec hit_point, t_obj *obj)
{
	typedef t_vec (*t_nf)(t_vec, t_obj *);
	const t_nf	jmp[] = {
		sphere_normal,
		cylinder_normal,
		cone_normal,
		plane_normal
	};
	return (jmp [obj->id](hit_point, obj));
}
