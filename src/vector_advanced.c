/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_advanced.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekantane <ekantane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 14:19:38 by ekantane          #+#    #+#             */
/*   Updated: 2023/01/30 15:17:37 by ekantane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

/* Normalize, or return a unit vector (magnitude scaled to 1) of v1.
*/
t_vec	vec_norm(t_vec v1)
{
	double	inv;

	inv = 1 / vec_len(v1);
	return (vec_scale(v1, inv));
}

t_vec	vec_scale(t_vec v1, double t)
{
	v1.x *= t;
	v1.y *= t;
	v1.z *= t;
	return (v1);
}

/* Return the cross prduct of two vectors.
*/
t_vec	vec_cross(t_vec u, t_vec v)
{
	return ((t_vec){
		.x = u.y * v.z - u.z * v.y,
		.y = u.z * v.x - u.x * v.z,
		.z = u.x * v.y - u.y * v.x
	});
}
