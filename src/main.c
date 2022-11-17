/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekantane <ekantane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 14:19:38 by ekantane          #+#    #+#             */
/*   Updated: 2022/11/17 20:43:48 by ikarjala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/rtv1.h"

int		shadow_init(t_light *light, t_sdl *sdl)
{
	double	max_t;
	double	t;
	t_vec	dir;

	t = 0;
	max_t = vec_len(vec_sub(light->pos, light->p));
	dir = vec_norm(vec_sub(light->pos, light->p));
	light->p = vec_sum(light->p, vec_scale(dir, EPS));
	t = sphere_intersect(light->p, dir, &sdl->obj[0]);
		if (t > 0.00001 && t < max_t)
			return (1);
	return (0);
}

void	get_intensity(t_sdl *sdl, t_light *light, t_vec v, double s)
{
	double	n_dot_l;
	double	r_dot_v;
	double	inten;
	t_vec	l;
	t_vec	r;

	light->new_inten = sdl->ambient;
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

//	a = vec_dot(dir, dir) - (1 + obj->r * obj->r);
//	b = 2 * (vec_dot(dir, oc) - (1 + obj->r * obj->r) * vec_dot(dir, obj->rot) * vec_dot(oc, obj->rot));
//	c = vec_dot(oc, oc) - (1 + obj->r * obj->r) * pow(vec_dot(oc, obj->rot), 2);

void	sphere(t_ray *ray, t_object *obj)
{
	obj->t = sphere_intersect(ray->orig, ray->dir, obj);
	obj->rot = vec_norm(obj->rot);
}

void	get_dir(double x, double y, t_ray *ray, t_sdl *sdl)
{
	ray->dir.x = x * (V_W / (double)DWIDTH);
	ray->dir.y = y * (V_H / (double)DHEIGHT);
	ray->dir.z = 1.0;
	ray->dir = vec_rot(ray->dir, sdl->cam.rot);
}

void	ray_trace_init(t_sdl *sdl, t_ray *ray)
{
	int		x;
	int		y;
	double	n_x;
	double	n_y;

	x = 0;
	while (x <= DWIDTH)
	{
		y = 0;
		n_x = (x + 0.5) / (double)DWIDTH;
		n_x = 2 * n_x - 1;
		while (y <= DHEIGHT)
		{
			n_y = (y + 0.5) / (double)DHEIGHT;
			n_y = 1 - (2 * n_y);
			get_dir(n_x, n_y, ray, sdl);
			sdl->min_t = INFINITY;
			sphere(ray, &sdl->obj[0]);
			sdl->light.p = vec_sum(ray->orig, vec_scale(ray->dir, OBJ.t));
			sdl->light.n = sphere_normal(ray, &OBJ);
			get_intensity(sdl, &sdl->light, vec_scale(ray->dir, -1), OBJ.specular);
			set_color(sdl, x, y);
			y++;
		}
		x++;
	}
}

void	init_sdl(t_sdl *sdl)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) >= 0)
		if ((sdl->wind = SDL_CreateWindow("RTv1", SDL_WINDOWPOS_UNDEFINED,
						SDL_WINDOWPOS_UNDEFINED, DWIDTH,
						DHEIGHT, SDL_WINDOW_SHOWN)))
			if ((sdl->rend = SDL_CreateRenderer(sdl->wind, -1,
							SDL_RENDERER_ACCELERATED)))
				return ;
	exit(0);
}

int		main(int argc, char **argv)
{
	t_sdl		sdl;
	t_ray		ray;
	SDL_Event	event;

	init_sdl(&sdl);
	ft_parse(argv[1], &sdl);
	if (argc != 2 || !argv[1])
		exit (1);
	ray.orig.x = sdl.cam.pos.x;
	ray.orig.y = sdl.cam.pos.y;
	ray.orig.z = sdl.cam.pos.z;
	ray_trace_init(&sdl, &ray);
	SDL_RenderPresent(sdl.rend);
	while (1)
		while (SDL_PollEvent(&event))
			if ((SDL_QUIT == event.type) || (SDL_KEYDOWN == event.type &&
				SDL_SCANCODE_ESCAPE == event.key.keysym.scancode))
				exit(0);
	return (0);
}
