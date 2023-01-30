/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_basic.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekantane <ekantane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 14:19:38 by ekantane          #+#    #+#             */
/*   Updated: 2023/01/30 15:17:19 by ekantane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

/* Return the Dot product between vectors v1 and v2
 * (scalar gotten by adding together the products of the individual axis).
*/
double	vec_dot(t_vec v1, t_vec v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

/* Return length (magnitude) of vector v1.
*/
double	vec_len(t_vec v1)
{
	return (sqrt(vec_dot(v1, v1)));
}

/* Return vector d, reflected by normal vector n
 * r = d - 2(d . n)n
*/
t_vec	vec_reflect(t_vec d, t_vec n)
{
	return (vec_sub (d, vec_scale (n, 2 * vec_dot(d, n))));
}

t_vec	vec_sum(t_vec v1, t_vec v2)
{
	v1.x += v2.x;
	v1.y += v2.y;
	v1.z += v2.z;
	return (v1);
}

t_vec	vec_sub(t_vec v1, t_vec v2)
{
	v1.x -= v2.x;
	v1.y -= v2.y;
	v1.z -= v2.z;
	return (v1);
}
