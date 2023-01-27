/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekantane <ekantane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 20:39:42 by ikarjala          #+#    #+#             */
/*   Updated: 2023/01/27 18:35:13 by ikarjala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static inline t_scene	scene_init(void)
{
	return ((t_scene){
		.obj = NULL, .obj_count = 0,
		.lights = NULL, .light_count = 0,
		.mat = NULL, .mat_count = 0,
		.default_mat = (t_mat){
		.color = (t_rgbf){1.0L, 1.0L, 1.0L},
		.gloss = 100.0L, .specular = 1.0
		},
		.cam = (t_cam){.pos = (t_vec){0, 0, -10}, .rot = (t_vec){0, 0, 0}},
		.ambient = 0.1L
	});
}

static inline t_parser	parser_init(void)
{
	return ((t_parser){
		.errorid = 0,
		.obj_count = 0,
		.light_count = 0,
		.mat_count = 0,
		.obj = NULL,
		.mat = NULL,
		.lights = NULL,
		.active_type = -1,
		.attr = (t_attr){.type = tnull, .val_req = 0},
		.av = {0},
		.line_num = 0
	});
}

static inline void	pre_process(char *line)
{
	const char	valid[] = "#<>(){}[]/+=:;,\t\v";
	char		*cp;

	cp = ft_strany (line, valid);
	while (cp)
	{
		if (*cp == '#')
		{
			*cp = 0;
			return ;
		}
		*cp = ' ';
		cp = ft_strany (cp, valid);
	}
}

static inline void	process_token(char *word, t_parser *p)
{
	if (p->attr.val_req != 0)
		set_attr (word, p);
	else if (!(token_try_obj (word, p)
			|| token_try_light (word, p)
			|| token_try_material (word, p)
			|| token_try_meta (word, p)
			|| token_try_attr (word, p)))
		parser_exception (p, word, MEPARSE_NOEXIST);
	free (word);
}

int	ft_parse(int fd, t_scene *ctx)
{
	t_parser	p;
	char		*line;
	char		**tokens;
	char		**ap;

	line = NULL;
	if (fd < 0)
		return (ft_panic (EM_FILE_ERROR, NULL));
	*ctx = scene_init ();
	p = parser_init ();
	p.default_matp = &ctx->default_mat;
	while (get_next_line(fd, &line) == RET_READL)
	{
		p.line_num ++;
		pre_process (line);
		tokens = ft_strsplit (line, ' ');
		ft_strdel (&line);
		ap = tokens;
		while (*ap)
			process_token (*(ap++), &p);
		ft_memdel ((void **)(&tokens));
	}
	ft_strdel (&line);
	close (fd);
	if (p.attr.val_req != 0)
		return (parser_exception (&p, NULL, MEPARSE_ARGC));
	scene_apply (ctx, &p);
	return (0);
}
