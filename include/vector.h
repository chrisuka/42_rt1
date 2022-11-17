/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikarjala <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 20:03:10 by ikarjala          #+#    #+#             */
/*   Updated: 2022/11/17 20:09:18 by ikarjala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_H
# define VECTOR_H

typedef struct s_vec
{
	double		x;
	double		y;
	double		z;
}	t_vec;

double	vec_len(t_vec v1);
double	vec_dot(t_vec v1, t_vec v2);

t_vec	vec_sum(t_vec v1, t_vec v2);
t_vec	vec_sub(t_vec v1, t_vec v2);

t_vec	vec_norm(t_vec v1);
t_vec	vec_scale(t_vec v1, double t);
t_vec	vec_rot(t_vec d, t_vec r);
t_vec	vec_rotx(t_vec d, double a);
t_vec	vec_roty(t_vec d, double a);
t_vec	vec_rotz(t_vec d, double a);

#endif
