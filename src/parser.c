/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekantane <ekantane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 20:39:42 by ikarjala          #+#    #+#             */
/*   Updated: 2023/01/04 18:30:00 by ekantane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int	ft_parse(char *arg, t_scene *ctx)
{
	char	*line;
	int		fd;
	int		i;
	char	**res;

	i = 0;
	fd = 0;
	line = NULL;
	if ((fd = open(arg, O_RDONLY)) < 0)
		exit(ft_panic ("Parse failed!", NULL));
	while (get_next_line(fd, &line) > 0)
	{
		res = ft_strsplit(line, ' ');
//		ft_strdel(&line);
	}
	*ctx = (t_scene){
		.cam = (t_cam){.pos = (t_vec){    (double)(atoi(res[0]))   , 0, -10}, .rot = (t_vec){0, 0, 0}},
		.obj[0] = (t_obj){.id = plane,
		.pos = (t_vec){2, 0, 0}, .rot = (t_vec){0}, .r = 2,
			.gloss = 200.0L, .specular = 1.0L, .color = (t_rgbf){1.0L, 0, 0}},
		.light = (t_light){.pos = (t_vec){-30, 50, -50}, .intensity = 0.4L},
		.ambient = 0.1L
	};
//		free(res[i++]);
	if (ft_strequ(res[1], "sphere"))
		ctx->obj[0] = (t_obj){.id = sphere};
	if (ft_strequ(res[1], "cylinder"))
		ctx->obj[0] = (t_obj){.id = cylinder};
	if (ft_strequ(res[1], "cone"))
		ctx->obj[0] = (t_obj){.id = cone};
	if (ft_strequ(res[1], "plane"))
		ctx->obj[0] = (t_obj){.id = plane};

//	ft_strdel(&line);
	close (fd);
	return (0);
}
