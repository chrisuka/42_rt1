/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekantane <ekantane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 12:18:05 by ikarjala          #+#    #+#             */
/*   Updated: 2023/01/30 14:30:59 by ekantane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H
# define RTV1_H

# include <SDL.h>
# include <stdio.h>
# include <fcntl.h>
# include <math.h>
# include <errno.h>

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

typedef unsigned int	t_uint;
typedef t_vec			(*t_normalfun)(t_vec, t_obj *);
typedef void			(*t_hookfun)(void);
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

t_obj	*find_nearest(t_scene *ctx, t_ray ray, double *min_t);
t_ray	project_ray_from_camera(int x, int y, t_cam cam);
t_rgbf	raytrace(t_scene *ctx, t_ray ray);

/*/ intersect.c ========================================================| ///*/

double	intersect(t_ray ray, t_obj obj);

/*/ intersect_solve.c ==================================================| ///*/

double	solve(double a, double b, double c);

/*/ error.c ============================================================| ///*/

void	*tense_malloc(const size_t bs);
int		ft_panic(const char *msg, void (*hook)(void));

/*/ render.c ===========================================================| ///*/

t_rgbf	cmul(t_rgbf c, double v);
t_uint	to_rgb(t_rgbf c);
void	set_color(t_sdl *sdl, int i, int x, int y);
void	render(t_sdl *sdl);

/*/ normals.c ==========================================================| ///*/

t_vec	get_object_normal(t_vec hit_point, t_obj *obj);

/*/ light.c ============================================================| ///*/

double	get_intensity(t_rt rt, t_light *lights, size_t lcount, t_mat m);

#endif
