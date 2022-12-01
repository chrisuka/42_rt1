/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekantane <ekantane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 14:19:38 by ekantane          #+#    #+#             */
/*   Updated: 2022/12/01 09:17:43 by ikarjala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static inline int	print_usage(void)
{
	const char	msg[] = "usage: " BIN_NAME " <scene_description_file>\n";
	
	write (1, msg, sizeof(msg) - sizeof(char));
	return (XC_ERROR);
}

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

#define DEBUG 0
#if DEBUG
#include <stdio.h>
static inline void	unit_tests(t_sdl *sdl)
{
	sdl = NULL;
}
#endif

/* args
 * parse
 * SDL init
 * events -> render -> raytrace
*/
int		main(int argc, char **argv)
{
	t_sdl		sdl;
	SDL_Event	event;

	if (argc != 2)
		return (print_usage ());
	else if (ft_parse (argv[1], &sdl.ctx) == -1
		|| init_sdl(&sdl) == -1)
		return (XC_ERROR);
#if DEBUG
	unit_tests(&sdl); // DEBUG
	return (0);
#endif
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
