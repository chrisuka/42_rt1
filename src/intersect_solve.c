/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_solve.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekantane <ekantane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 11:36:51 by ikarjala          #+#    #+#             */
/*   Updated: 2023/01/30 15:15:52 by ekantane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

/* Solve quadratic function and return the more ideal solution to get
 * the closest real intersection t, or -1 if there are no real roots.
 *
 * D = discriminant
 * D = b*b - 4ac
 *   D > 0: there are two intersections.
 *   D = 0: there is one intersection.
 *   D < 0: there are no intersections.
 *
 * t will be used as a scalar representing the distance
 * from ray origin to the closest intersection point.
*/

double	solve(double a, double b, double c)
{
	const double	d = b * b - 4 * a * c;
	double			d_root;
	double			aa_inv;
	double			t1;
	double			t2;

	if (d < 0)
		return (-1);
	d_root = sqrt(d);
	aa_inv = 1 / (2 * a);
	t1 = (-b - d_root) * aa_inv;
	t2 = (-b + d_root) * aa_inv;
	if ((t1 <= t2 && t1 >= 0) || (t1 >= 0 && t2 < 0))
		return (t1);
	else if ((t2 <= t1 && t2 >= 0) || (t1 < 0 && t2 >= 0))
		return (t2);
	return (-1);
}
