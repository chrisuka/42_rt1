/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekantane <ekantane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 13:02:04 by ikarjala          #+#    #+#             */
/*   Updated: 2022/12/03 17:16:34 by ekantane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

#if 0
static inline t_vec	cone_normal(t_vec dir, t_vec hit_p, t_obj *obj)
{
	t_vec	n;
	double	m;

	m = vec_dot(dir, obj->rot) * T + vec_dot(vec_sub(RAYSTART, obj->pos), obj->rot);
	n = vec_scale(vec_scale(obj->rot, m), (1 + obj->rot * obj->rot));
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
#endif

/* Return the normal vector of ray intersection point on an sphere's surface.
 * N = Normalize(P - O)
 * where P = ray hit point, O = object origin
*/

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
		//cylinder_normal,
		//cone_normal,
		plane_normal
	};

	return (jmp [sphere](dir, hit_point, obj));
}
