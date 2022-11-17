/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekantane <ekantane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 14:20:34 by ekantane          #+#    #+#             */
/*   Updated: 2022/11/17 18:12:17 by ikarjala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H
# define RTV1_H

# include "../libft/libft.h"
# include <SDL2/SDL.h>
# include <stdio.h>
# include <fcntl.h>
# include <math.h>

# define DWIDTH		800
# define DHEIGHT	800
# define V_W		40
# define V_H		40
# define EPS		0.000001

// WARN: get rid of these macros ASAP! they are forbidden!
# define DTR(a)	((double)a * (M_PI / 180))
# define OBJ sdl->obj[0]
# define SPL spl_res[0]
// =======================

// vector.h
typedef struct s_vec
{
	double		x;
	double		y;
	double		z;
}	t_vec;

// render.h
typedef struct s_rgb
{
	float	r;
	float	g;
	float	b;
}	t_rgb;

// scene.h
typedef struct s_light
{
	t_vec	pos;
	t_vec	p;
	t_vec	n;
	double	inten;
	double	new_inten;
}	t_light;

typedef struct s_object
{
	t_vec	pos;
	t_rgb	col;
	t_vec	rot;
	double	r;
	double	t;
	int		name;
	int		no_intersect;
	double	specular;
}	t_object;

typedef struct s_cam
{
	t_vec	pos;
	t_vec	rot;
}	t_cam;

typedef struct s_ray
{
	t_vec	orig;
	t_vec	dir;
}	t_ray;

// rtv1.h
typedef struct s_sdl
{
	SDL_Window		*wind;
	SDL_Renderer	*rend;
	t_cam			cam;
	t_object		*obj;
	double			min_t;
	double			ambient;
	t_light			light;
}	t_sdl;

int		shadow_init(t_light *light, t_sdl *sdl);
void	get_intensity(t_sdl *sdl, t_light *light, t_vec v, double s);
void	get_dir(double x, double y, t_ray *ray, t_sdl *sdl);
void	set_color(t_sdl *sdl, int x, int y);
void	ray_trace_init(t_sdl *sdl, t_ray *ray);
t_vec	sphere_normal(t_ray *ray, t_object *obj);
double	get_t(double a, double b, double d);
double	sphere_intersect(t_vec o, t_vec dir, t_object *obj);
void	sphere(t_ray *ray, t_object *obj);
void	ft_parse(char *arg, t_sdl *sdl);
void	init_sdl(t_sdl *sdl);
int		main(int argc, char **argv);

t_vec	vec_sum(t_vec v1, t_vec v2);
double	vec_dot(t_vec v1, t_vec v2);
double	vec_len(t_vec v1);
t_vec	vec_scale(t_vec v1, double t);
t_vec	vec_norm(t_vec v1);
t_vec	vec_sub(t_vec v1, t_vec v2);
t_vec	vec_rot(t_vec d, t_vec r);
t_vec	vec_rotx(t_vec d, double a);
t_vec	vec_roty(t_vec d, double a);
t_vec	vec_rotz(t_vec d, double a);

#endif
