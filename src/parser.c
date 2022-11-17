/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikarjala <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 20:39:42 by ikarjala          #+#    #+#             */
/*   Updated: 2022/11/17 20:50:08 by ikarjala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	ft_parse(char *arg, t_sdl *sdl)
{
	char	*line;
	int		fd;
	int		i;
	char	**spl_res;

	i = 0;
	fd = 0;
	line = NULL;
	sdl->obj = ft_memalloc(sizeof(t_object));
	if ((fd = open(arg, O_RDONLY)) < 0)
		exit(1);
	while ((i = get_next_line(fd, &line)) > 0)
	{
		spl_res = ft_strsplit(line, ' ');
	if (ft_strequ(spl_res[0], "sphere.pos.x"))
		OBJ.pos.x = (double)(atoi(spl_res[1]));
	else if (ft_strequ(spl_res[0], "sphere.pos.y"))
		OBJ.pos.y = (double)(atoi(spl_res[1]));
	else if (ft_strequ(spl_res[0], "sphere.pos.z"))
		OBJ.pos.z = (double)(atoi(spl_res[1]));
	else if (ft_strequ(spl_res[0], "sphere.rot.x"))
		OBJ.rot.x = (double)(atoi(spl_res[1]));
	else if (ft_strequ(spl_res[0], "sphere.rot.y"))
		OBJ.rot.y = (double)(atoi(spl_res[1]));
	else if (ft_strequ(spl_res[0], "sphere.rot.z"))
		OBJ.rot.z = (double)(atoi(spl_res[1]));
	else if (ft_strequ(spl_res[0], "sphere.radius"))
		OBJ.r = (double)(atoi(spl_res[1]));
	else if (ft_strequ(spl_res[0], "light.pos.x"))
		sdl->light.pos.x = (double)(atoi(spl_res[1]));
	else if (ft_strequ(spl_res[0], "light.pos.y"))
		sdl->light.pos.y = (double)(atoi(spl_res[1]));
	else if (ft_strequ(spl_res[0], "light.pos.z"))
		sdl->light.pos.z = (double)(atoi(spl_res[1]));
	else if (ft_strequ(spl_res[0], "colorR"))
		OBJ.col.rgb[0] = (unsigned char)(atoi(spl_res[1]));
	else if (ft_strequ(spl_res[0], "colorB"))
		OBJ.col.rgb[1] = (unsigned char)(atoi(spl_res[1]));
	else if (ft_strequ(spl_res[0], "colorG"))
		OBJ.col.rgb[2] = (unsigned char)(atoi(spl_res[1]));
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
	OBJ.specular = (double)(atoi(spl_res[1]));
	ft_strdel(&line);
	}
	ft_strdel(&line);
}
