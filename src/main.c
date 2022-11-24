/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekantane <ekantane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 14:19:38 by ekantane          #+#    #+#             */
/*   Updated: 2022/11/24 20:21:35 by ikarjala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

#if 0

SHADOW_INIT & GET_INTENSITY:

n_dot_l = the point where the normal meets the light
r_dot_v = the point where the ray meets the "view vector"
pos = the position of the light
p = any point in the scene

The ambience is the base for the intensity and
we substract point from postion to create an omnidirectional light.
If there are no shadows, the intensity is zero.

"if (n_dot_l > EPS)" makes sure we don’t add negative values, which represent
lights illuminating the back side of the surface. After this we caculate the intensity and 
before shadow_init checks for the closest intersection.

The position of the point of reflection will be slightly different from the ideal value,
and the distance that should be 0 will more likely be some small quantity like 0.000001.
That's what we call an epsilon.

Similar things happen with specular:
Again, "if (r_dot_v > EPS)" makes sure we don’t add negative values, which represent
lights illuminating the back side of the surface.

static int	shadow_init(t_light *light, t_sdl *sdl)
{
	double	max_t;
	double	t;

	t_vec	dir;

	t = 0;
	max_t = vec_len(vec_sub(light->pos, light->p));
	dir = vec_norm(vec_sub(light->pos, light->p));
	light->p = vec_sum(light->p, vec_scale(dir, EPS));
	t = cone_intersect(light->p, dir, &sdl->ctx.obj);
	if (t > EPS && t < max_t)
		return (1);
	return (0);
}

static void	get_intensity(t_sdl *sdl, t_light *light, t_vec v, double s)
{
	double	n_dot_l;
	double	r_dot_v;
	double	inten;
	t_vec	l;
	t_vec	r;

	light->new_inten = sdl->ctx.ambient;
	inten = 0.0;
	l = vec_norm(vec_sub(light->pos, light->p));
	n_dot_l = vec_dot(light->n, l);
	if (shadow_init(light, sdl) == 0)
		inten = light->inten;
	if (n_dot_l > EPS)
		light->new_inten += inten * (n_dot_l / (vec_len(light->n) * vec_len(l)));
	if (s > 0)
	{
		r = vec_scale(light->n, 2);
		r = vec_scale(r, vec_dot(light->n, l));
		r = vec_sub(r, l);
		r_dot_v = vec_dot(r, v);
		if (r_dot_v > EPS)
			light->new_inten += inten * pow((r_dot_v / (vec_len(r) * vec_len(v))), s);
	}
}

t_vec	cone_normal(t_ray *ray, t_object *obj)
{
	double	m;
	t_vec	n;
	t_vec	p;

	m = obj->t * vec_dot(ray->dir, obj->rot) +
	vec_dot(vec_sub(ray->orig, obj->pos), obj->rot);
	p = vec_sum(ray->orig, vec_scale(ray->dir, obj->t));
	n = vec_scale(vec_scale(obj->rot, m), (1 + obj->r * obj->r));
	n = vec_norm(vec_sub(vec_sub(p, obj->pos), n));
	if (vec_dot(ray->dir, n) > EPS)
		n = vec_scale(n, -1);
	return (n);
}

t_vec	cylinder_normal(t_ray *ray, t_object *obj)
{
	double	m;
	t_vec	n;
	t_vec	p;

	m = obj->t * vec_dot(ray->dir, obj->rot) +
	vec_dot(vec_sub(ray->orig, obj->pos), obj->rot);
	p = vec_sum(ray->orig, vec_scale(ray->dir, obj->t));
	n = vec_norm(vec_sub(vec_sub(p, obj->pos), vec_scale(obj->rot, m)));
	if (vec_dot(ray->dir, n) > EPS)
		n = vec_scale(n, -1);
	return (n);
}

double	cone_intersect(t_vec o, t_vec dir, t_object *obj)
{
	double	a;
	double	b;
	double	c;
	double	d;
	t_vec	x;
	double	m;

	m = pow(obj->r, 2) / vec_dot(dir, dir);
	x = vec_sub(o, obj->pos);
	
	a = vec_dot(dir, dir) - m * pow(vec_dot(dir, obj->rot), 2) - pow(vec_dot(dir, obj->rot), 2);
	b = 2 * ((vec_dot(dir, x) - (m * vec_dot(dir, obj->rot)) * vec_dot(x, obj->rot) - vec_dot(dir, obj->rot) * vec_dot(x, obj->rot)));
	c = vec_dot(x, x) - (m * pow(vec_dot(x, obj->rot), 2)) - pow(vec_dot(x, obj->rot), 2);
	d = b * b - 4 * a * c;
	if (d < 0)
		return (-1);
	return (get_t(a, b, d));
}

double	cylinder_intersect(t_vec o, t_vec dir, t_object *obj)
{
	double	a;
	double	b;
	double	c;
	double	d;
	t_vec	x;

	x = vec_sub(o, obj->pos);
	a = vec_dot(dir, dir) - pow(vec_dot(dir, obj->rot), 2);
	b = 2 * (vec_dot(dir, x) - (vec_dot(dir, obj->rot) * vec_dot(x, obj->rot)));
	c = vec_dot(x, x) - pow(vec_dot(x, obj->rot), 2) - pow(obj->r, 2);
	d = b * b - 4 * a * c;
	if (d < 0)
		return (-1);
	return (get_t(a, b, d));
}

t_vec	sphere_normal(t_ray *ray, t_object *obj)
{
	t_vec n;

	n = vec_sum(ray->orig, vec_scale(ray->dir, obj->t));
	n = vec_norm(vec_sub(n, obj->pos));
	if (vec_dot(ray->dir, n) > EPS)
		n = vec_scale(n, -1);
	return (n);
}

double	get_t(double a, double b, double d)
{
	double t1;
	double t2;

	t1 = (-b - sqrt(d)) / (2 * a);
	t2 = (-b + sqrt(d)) / (2 * a);
	if ((t1 <= t2 && t1 >= 0) || (t1 >= 0 && t2 < 0))
		return (t1);
	else if ((t2 <= t1 && t2 >= 0) || (t1 < 0 && t2 >= 0))
		return (t2);
	return (-1);
}

double	sphere_intersect(t_vec o, t_vec dir, t_object *obj)
{
	double	a;
	double	b;
	double	c;
	double	d;
	t_vec	oc;

	oc = vec_sub(o, obj->pos);
	a = vec_dot(dir, dir);
	b = 2 * vec_dot(oc, dir);
	c = vec_dot(oc, oc) - (obj->r * obj->r);
	d = b * b - 4 * a * c;
	if (d < 0)
		return (-1);
	return (get_t(a, b, d));
}

void	object_init(t_sdl *sdl, t_ray *ray, int i, t_object *obj)
{
	obj->t = cone_intersect(ray->orig, ray->dir, obj);
	obj->rot = vec_norm(obj->rot);
	if (obj->t > 0 && obj->t < sdl->ctx.min_t)
	{
		sdl->ctx.min_t = obj->t;
		sdl->ctx.clos_obj = i;
	}
}

void	ray_trace_init(t_sdl *sdl, t_ray *ray)
{
	int		x;
	int		y;
	int		i;

#if 0
	double	n_x;
	double	n_y;
#endif

	x = 0;
	i = 1;

	while (x <= WIN_W)
	{
		y = 0;
#if 0
		n_x = (x + 0.5) / (double)WIN_W;
		n_x = 2 * n_x - 1;
#endif
		while (y <= WIN_H)
		{
#if 0
			n_y = (y + 0.5) / (double)WIN_H;
			n_y = 1 - (2 * n_y);
#endif
			//get_dir(n_x, n_y, ray, sdl);
			sdl->ctx.min_t = INFINITY;
			sdl->ctx.clos_obj = 0;
			object_init(sdl, ray, i, &sdl->ctx.obj);
			sdl->ctx.light.p = vec_sum(ray->orig, vec_scale(ray->dir, sdl->ctx.obj.t));
			sdl->ctx.light.n = cone_normal(ray, &sdl->ctx.obj);
			get_intensity(sdl, &sdl->ctx.light, vec_scale(ray->dir, -1), sdl->ctx.obj.specular);
			set_color(sdl, sdl->ctx.clos_obj, x, y);
			y++;
		}
		x++;
	}
}
#endif

static inline int	init_sdl(t_sdl *sdl)
{
	const char	error_msg[] = "Unable to initialize SDL.";
	const void	(*errhook) = NULL;

	sdl->pstatus = ECONTINUE;
	if (SDL_Init (esdl_dev) != 0)
		return (ft_panic (error_msg, errhook));
	sdl->win = SDL_CreateWindow (
		WIN_TITLE, esdl_winpos, esdl_winpos,
		WIN_W, WIN_H, esdl_winflags);
	sdl->surf = SDL_GetWindowSurface (sdl->win);
	if (!sdl->win || !sdl->surf)
		return (ft_panic (error_msg, errhook));
	return (0);
}

/* args
 * parse
 * SDL init
 * events -> render
*/
int		main(int argc, char **argv)
{
	t_sdl		sdl;
	t_ray		ray;
	SDL_Event	event;

	if (argc != 2 || !argv[1] // TODO: print usage
		|| ft_parse (argv[1], &sdl) == -1
		|| init_sdl(&sdl) == -1)
		return (XC_ERROR);
	ray = (t_ray){.orig = sdl.ctx.cam.pos, .dir = (t_vec){0, 0, 1}};
	//ray_trace_init(&sdl, &ray);
	render (&sdl);
	while (sdl.pstatus == ECONTINUE)
	{
		while (SDL_PollEvent(&event))
		{
			if ((SDL_QUIT == event.type) || (SDL_KEYDOWN == event.type
			&& SDL_SCANCODE_ESCAPE == event.key.keysym.scancode))
				sdl.pstatus = EEXIT;
		}
	}
	// free everything here, then exit with main return
	SDL_Quit ();
	return (XC_EXIT);
}
