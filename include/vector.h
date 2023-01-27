/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekantane <ekantane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 20:03:10 by ikarjala          #+#    #+#             */
/*   Updated: 2023/01/27 18:19:25 by ikarjala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_H
# define VECTOR_H

# include <math.h>

typedef struct s_vec
{
	double	x;
	double	y;
	double	z;
}	t_vec;

double	vec_len(t_vec v1);
double	vec_dot(t_vec v1, t_vec v2);

t_vec	vec_reflect(t_vec d, t_vec n);

t_vec	vec_sum(t_vec v1, t_vec v2);
t_vec	vec_sub(t_vec v1, t_vec v2);

t_vec	vec_norm(t_vec v1);
t_vec	vec_scale(t_vec v1, double t);
t_vec	vec_rot(t_vec dir, t_vec rot);
t_vec	vec_cross(t_vec u, t_vec v);

#endif
