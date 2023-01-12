/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekantane <ekantane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 20:39:42 by ikarjala          #+#    #+#             */
/*   Updated: 2023/01/12 19:38:05 by ikarjala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static inline t_scene	scene_init(void)
{
	return ((t_scene){
		.obj = NULL,	.obj_count = 0,
		.lights = NULL,	.light_count = 0,
		.mat = NULL,	.mat_count = 0,
		.default_mat = (t_mat){
			.color = (t_rgbf){0.5L, 0.2L, 0}, .gloss = 0.0L, .specular = 0.0
		},
		.cam = (t_cam){.pos = (t_vec){0, 0, -10}, .rot = (t_vec){0, 0, 0}},
		.ambient = 0.1L
	});
}

static inline t_parser	parser_init(void)
{
	return ((t_parser){
		.obj = NULL,
		.mat = NULL,
		.lights = NULL,
		.attrp = NULL,
		.attr_val_req = 0,
		.errorid = 0,

		//.line_num = 0,
		.obj_count = 0,
		.light_count = 0,
		.mat_count = 0,
	});
}

static inline void	pre_process(char *line)
{
	const char	valid[] = "#<>(){}[]+=:;,\t\v";
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
#if 1
{
	if (p->attr_val_req != 0)
	{
		//set_attr (word, p);
		parser_exception (EPARSE_INTERNAL);
	}
	else if (token_try_obj (word, p))
		//p->obj->next = obj_init ( CHECK_OBJ_ID ); // WARN: list is null at start
		write (1, "obj\n", 4);
	#if 0
	else if (token_try_attr (word, p))
	{
		//p->attrp = get_attr_pointer (word, atype); // must set avr !
	}
	//else if (atype == mat)
	else if (atype == light)
	else if (atype == attr)
	else if (atype == meta_cam)
		p->arg_type = meta_cam;
	#endif
	else
		parser_exception (EPARSE_TOKEN_UNKNOWN);
	free (word);
}
#else
{
	p = NULL;
	ft_putendl (word);
}
#endif

#if 1
// NOTE: ONLY FOR DEBUG!!
/* Rotation is actually a vector, needs to be changed later.
*/
void	scene_hard_set_attr(t_scene *ctx)
{
	ctx->cam = (t_cam){.pos = (t_vec){0, 0, -200}, .rot = (t_vec){0, 0, 0}};
	ctx->obj[0] = (t_obj){.id = sphere,
			.pos = (t_vec){20, 0, -100}, .rot = (t_vec){0}, .r = 8};
	ctx->obj[1] = (t_obj){.id = cylinder,
			.pos = (t_vec){5, 0, 0}, .rot = (t_vec){0, 1, 0}, .r = 5};
	ctx->obj[2] = (t_obj){.id = cone,
			.pos = (t_vec){-20, 0, 0}, .rot = (t_vec){0, 1, 0}, .r = 0.11};
	ctx->obj[3] = (t_obj){.id = plane,
			.pos = (t_vec){0, -10, 0}, .rot = (t_vec){0, 1, 0}, .r = 1};
	//ctx->light = (t_light){.pos = (t_vec){-200, 30, -300}, .intensity = 0.7L},
	//.gloss = 200.0L, .specular = 0.1L, .color = (t_rgbf){0, 1.0L, 0.0L}};
	ctx->ambient = 0.1L;
}

int	ft_parse(int fd, t_scene *ctx)
{
	t_parser	p;
	char		*line;
	char		**tokens;
	char		**ap;

	line = NULL;
	if (fd < 0)
		exit (parser_error_fatal (EPARSE_FILE_ERROR));
	*ctx = scene_init ();
	p = parser_init ();
	while (get_next_line(fd, &line) != 0) // TODO: handle gnl error code
	{
		#if 0
		if (ft_strchr (line, '#'))
		{
			ft_strdel(&line);
			continue ;
		}
		#endif
		pre_process (line); // TODO: error checks
		tokens = ft_strsplit (line, ' ');
		ft_strdel(&line);
		ap = tokens;
		while (*ap)
			process_token (*(ap++), &p);
		ft_memdel ((void **)(&tokens));
	}
	ft_strdel(&line);
	close (fd);
	scene_apply (ctx, &p);
	// DEBUG!!========
	scene_hard_set_attr (ctx);
	return (0);
}

#endif
