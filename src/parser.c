/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekantane <ekantane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 20:39:42 by ikarjala          #+#    #+#             */
/*   Updated: 2022/11/24 09:19:18 by ikarjala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/rtv1.h"

void	ft_parse(char *arg, t_sdl *sdl)
{
	char	*line;
	int		fd;
	int		i;
	char	**spl_res;

	i = 0;
	fd = 0;
	line = NULL;
	if ((fd = open(arg, O_RDONLY)) < 0)
		exit(ft_panic ("Parse failed!", NULL));
	while ((i = get_next_line(fd, &line)) > 0)
	{
		spl_res = ft_strsplit(line, ' ');
	if (ft_strequ(spl_res[0], "sphere.pos.x"))
		sdl->obj.pos.x = (double)(atoi(spl_res[1]));
	else if (ft_strequ(spl_res[0], "sphere.pos.y"))
		sdl->obj.pos.y = (double)(atoi(spl_res[1]));
	else if (ft_strequ(spl_res[0], "sphere.pos.z"))
		sdl->obj.pos.z = (double)(atoi(spl_res[1]));
	else if (ft_strequ(spl_res[0], "sphere.rot.x"))
		sdl->obj.rot.x = (double)(atoi(spl_res[1]));
	else if (ft_strequ(spl_res[0], "sphere.rot.y"))
		sdl->obj.rot.y = (double)(atoi(spl_res[1]));
	else if (ft_strequ(spl_res[0], "sphere.rot.z"))
		sdl->obj.rot.z = (double)(atoi(spl_res[1]));
	else if (ft_strequ(spl_res[0], "sphere.radius"))
		sdl->obj.r = (double)(atoi(spl_res[1]));
	else if (ft_strequ(spl_res[0], "light.pos.x"))
		sdl->light.pos.x = (double)(atoi(spl_res[1]));
	else if (ft_strequ(spl_res[0], "light.pos.y"))
		sdl->light.pos.y = (double)(atoi(spl_res[1]));
	else if (ft_strequ(spl_res[0], "light.pos.z"))
		sdl->light.pos.z = (double)(atoi(spl_res[1]));
	else if (ft_strequ(spl_res[0], "colorR"))
		sdl->obj.col.r = (unsigned char)(atoi(spl_res[1]));
	else if (ft_strequ(spl_res[0], "colorB"))
		sdl->obj.col.g = (unsigned char)(atoi(spl_res[1]));
	else if (ft_strequ(spl_res[0], "colorG"))
		sdl->obj.col.b = (unsigned char)(atoi(spl_res[1]));
	else if (ft_strequ(spl_res[0], "light.intensity"))
		sdl->light.inten = (double)(atoi(spl_res[1])) / 100;
	else if (ft_strequ(spl_res[0], "cam.pos.x"))
		sdl->cam.pos.x = (double)(atoi(spl_res[1]));
	else if (ft_strequ(spl_res[0], "cam.pos.y"))
		sdl->cam.pos.y = (double)(atoi(spl_res[1]));
	else if (ft_strequ(spl_res[0], "cam.pos.z"))
		sdl->cam.pos.z = (double)(atoi(spl_res[1]));
	else if (ft_strequ(spl_res[0], "cam.rot.x"))
		sdl->cam.rot.x = (double)(atoi(spl_res[1]));
	else if (ft_strequ(spl_res[0], "cam.rot.y"))
		sdl->cam.rot.y = (double)(atoi(spl_res[1]));
	else if (ft_strequ(spl_res[0], "cam.rot.z"))
		sdl->cam.rot.z = (double)(atoi(spl_res[1]));
	else if (ft_strequ(spl_res[0], "ambient"))
		sdl->ambient = (double)(atoi(spl_res[1])) / 100;
	else if (ft_strequ(spl_res[0], "specular"))
	sdl->obj.specular = (double)(atoi(spl_res[1]));
	ft_strdel(&line);
	}
	ft_strdel(&line);
}
