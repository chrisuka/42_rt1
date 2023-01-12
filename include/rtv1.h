/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikarjala <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 12:18:05 by ikarjala          #+#    #+#             */
/*   Updated: 2023/01/12 13:24:44 by ikarjala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H
# define RTV1_H

# include <SDL.h>
# include <stdio.h>
# include <fcntl.h>
# include <math.h>

# include "libft.h"
# include "get_next_line.h"
# include "vector.h"
# include "scene.h"
# include "parser.h"
# include "render.h"
# include "graphics_util.h"

# define BIN_NAME	"rtv1"
# define WIN_TITLE	"RT (v1)"
# define WIN_W		800
# define WIN_H		800

# define MAX_BOUNCE	2

# define VIEWPORT_W	400.0L
# define VIEWPORT_H	400.0L
# define EPS		0.000001

# define ECONTINUE	0
# define EEXIT		1
# define EINTERNAL	2

# define XC_EXIT	0
# define XC_ERROR	1

typedef struct s_sdl_data
{
	int				ps;
	SDL_Window		*win;
	SDL_Surface		*surf;

	t_scene			ctx;
}	t_sdl;

/*/ parser.c ===========================================================| ///*/

int		ft_parse(int fd, t_scene *ctx);

/*/ raytracer.c ========================================================| ///*/

t_ray	project_ray_from_camera(int x, int y, t_cam cam);
t_rgbf	raytrace(t_scene *ctx, t_ray ray);

/*/ intersect.c ========================================================| ///*/

double	intersect(t_ray ray, t_obj obj);

/*/ error.c ============================================================| ///*/

int		ft_panic(const char *msg, void (*hook)(void));

/*/ render.c ===========================================================| ///*/

void	set_color(t_sdl *sdl, int i, int x, int y);
void	render(t_sdl *sdl);

/*/ normals.c ==========================================================| ///*/

t_vec	get_object_normal(t_vec dir, t_vec hit_point, t_obj *obj);

/*/ light.c ============================================================| ///*/

double	get_intensity(t_vec hit_p, t_vec hit_n, t_light light, t_obj *obj);

#endif
