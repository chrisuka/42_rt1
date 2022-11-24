/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekantane <ekantane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 14:20:34 by ekantane          #+#    #+#             */
/*   Updated: 2022/11/24 10:27:02 by ikarjala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H
# define RTV1_H

# include <SDL.h>
# include <stdio.h>
# include <fcntl.h>
# include <math.h>

# include "libft.h"
# include "vector.h"
# include "scene.h"
# include "render.h"

# define BIN_NAME	"rtv1"
# define WIN_TITLE	"RT (v1)"
# define WIN_W		800
# define WIN_H		800

# define MAX_BOUNCE	2

# define V_W		40
# define V_H		40
# define EPS		0.000001

# define ECONTINUE	0
# define EEXIT		1

# define XC_EXIT	0
# define XC_ERROR	1

typedef struct s_sdl_data
{
	unsigned int	pstatus;
	SDL_Window		*win;
	SDL_Renderer	*rend;
	SDL_Surface		*surf;

	// TODO: move these to s_context in scene.h
	t_cam			cam;
	t_object		obj;
	double			min_t;
	int				clos_obj;
	double			ambient;
	t_light			light;
	int				spl_res[0];
	// ========================================
}	t_sdl;

void	object_init(t_sdl *sdl, t_ray *ray, int i, t_object *obj);
void	cylinder(t_sdl *sdl, t_ray *ray, int i, t_object *obj);

t_vec	cylinder_normal(t_ray *ray, t_object *obj);
t_vec	sphere_normal(t_ray *ray, t_object *obj);

void	light(t_sdl *sdl, t_ray *ray);

/*/ parser.c ===========================================================| ///*/

void	ft_parse(char *arg, t_sdl *sdl);
/*/ raytracer.c ========================================================| ///*/
t_ray	project_ray_from_camera(t_cam cam);
t_rgbf	raytrace(t_ray ray);

void	ray_trace_init(t_sdl *sdl, t_ray *ray);
//void	get_dir(double x, double y, t_ray *ray, t_sdl *sdl);
double	get_t(double a, double b, double d);
/*/ intersect.c ========================================================| ///*/

double	sphere_intersect(t_vec o, t_vec dir, t_object *obj);
double	cylinder_intersect(t_vec o, t_vec dir, t_object *obj);
double	cone_intersect(t_vec o, t_vec dir, t_object *obj);
void	intersection_check(t_ray *ray, t_sdl *sdl, int x, int y);
/*/ error.c ============================================================| ///*/

int		ft_panic(const char *msg, void (*hook)(void));
/*/ render.c ===========================================================| ///*/

void	set_color(t_sdl *sdl, int i, int x, int y);
void	render(t_sdl *sdl);
/*/ color.c ============================================================| ///*/

unsigned int	to_rgb(t_rgbf c);
#endif
