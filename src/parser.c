/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekantane <ekantane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 20:39:42 by ikarjala          #+#    #+#             */
/*   Updated: 2023/01/09 13:56:11 by ekantane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

/* Rotation is actually a vector, needs to be changed later.
*/

int	ft_parse(char *arg, t_scene *ctx)
{
	char	*line;
	int		fd;
	int		i;
	
	i = 0;
	fd = 0;
	line = NULL;
	if ((fd = open(arg, O_RDONLY)) < 0)
		exit(ft_panic ("Parse failed!", NULL));
	*ctx = (t_scene){
		.cam = (t_cam){.pos = (t_vec){    0  , 0, -70}, .rot = (t_vec){0, 0, 0}},
		.obj[0] = (t_obj){.id = sphere,
			.pos = (t_vec){20, 0, 0}, .rot = (t_vec){0}, .r = 8,
			.gloss = 0.0L, .specular = 0.0L, .color = (t_rgbf){1.0L, 0, 0}},
		.obj[1] = (t_obj){.id = cylinder,
			.pos = (t_vec){-5, 0, 0}, .rot = (t_vec){0, 1, 0}, .r = 5,
			.gloss = 0.0L, .specular = 0.0L, .color = (t_rgbf){1.0L, 1.0L, 0}},
		.obj[2] = (t_obj){.id = cone,
			.pos = (t_vec){-20, 0, 0}, .rot = (t_vec){0, 1, 0}, .r = 0.11,
			.gloss = 0.0L, .specular = 0.0L, .color = (t_rgbf){0, 1.0L, 1.0L}},
		.light = (t_light){.pos = (t_vec){-200, 0, 0}, .intensity = 0.7L},
		.ambient = 0.1L
	};
	close (fd);
	return (0);
}
