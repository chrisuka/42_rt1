/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekantane <ekantane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 20:03:10 by ikarjala          #+#    #+#             */
/*   Updated: 2023/01/07 18:56:57 by ekantane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_H
# define VECTOR_H

# include <math.h>

// WARN: get rid of these macros ASAP! they are forbidden!
# define DTR(a)	((double)a * (M_PI / 180))
// DTR = degrees to radians

typedef struct s_vec
{
	double		x;
	double		y;
	double		z;
}	t_vec;

double	vec_len(t_vec v1);
double	vec_dot(t_vec v1, t_vec v2);

t_vec	vec_reflect(t_vec d, t_vec n);

t_vec	vec_sum(t_vec v1, t_vec v2);
t_vec	vec_sub(t_vec v1, t_vec v2);

t_vec	vec_norm(t_vec v1);
t_vec	vec_scale(t_vec v1, double t);
t_vec	vec_rot(t_vec d, t_vec r);
t_vec	vec_rotx(t_vec d, double a);
t_vec	vec_roty(t_vec d, double a);
t_vec	vec_rotz(t_vec d, double a);
t_vec vec_cross(t_vec u, t_vec v);

#endif
