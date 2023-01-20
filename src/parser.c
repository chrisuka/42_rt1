/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekantane <ekantane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 20:39:42 by ikarjala          #+#    #+#             */
/*   Updated: 2023/01/20 15:42:41 by ikarjala         ###   ########.fr       */
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
			//.color = (t_rgbf){0.5L, 0.2L, 0.0L},
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

		//.line_num = 0,
		.default_matp = NULL,
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
#if 1
{
	if (p->attr.val_req != 0)
	{
		set_attr (word, p);
		//parser_exception (EPARSE_INTERNAL);
	}
	else if (token_try_obj (word, p))
		write (1, "obj\n", 4);
	else if (token_try_light (word, p))
		write (1, "light\n", 6);
	else if (token_try_material (word, p))
		write (1, "material\n", 9);
	else if (token_try_meta (word, p))
		write (1, "scene metadata\n", 15);
	#if 1
	else if (token_try_attr (word, p))
	{
		write (1, "attr: ", 6);
		ft_putendl (word);
	}
	#endif
	else
	{
		write (1, "ayo?! ", 6);
		ft_putendl (word);
		parser_exception (EPARSE_TOKEN_UNKNOWN);
	}
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
	/*
	ctx->obj[0] = (t_obj){.id = sphere,
		.pos = (t_vec){20, 0, 0}, .rot = (t_vec){0}, .r = 2,
		.mat = &ctx->default_mat};

	ctx->obj[1] = (t_obj){.id = cylinder,
		.pos = (t_vec){5, 0, 0}, .rot = (t_vec){0, 1, 0}, .r = 1,
		.mat = &ctx->default_mat};

	ctx->obj[3] = (t_obj){.id = plane,
		.pos = (t_vec){0, -10, 0}, .rot = (t_vec){0, 1, 0}, .r = 1,
		.mat = &ctx->default_mat};
	*/

	//ctx->light_count = 1;
	//ctx->lights = (t_light *)malloc(sizeof(t_light));
	ctx->lights[0].intensity = 0.4L;
	//ctx->mat[0] = (t_mat){.color = (t_rgbf){.r = 1.0L, .g = 0.0L, .b = 0.0L}};

	//ctx->cam = (t_cam){.pos = (t_vec){0, 10, -100}, .rot = (t_vec){0, 0, 0}};
	ctx->ambient = 0.3;
}
#endif

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
	p.default_matp = &ctx->default_mat;
	while (get_next_line(fd, &line) != RET_EOF) // TODO: handle gnl error code
	{
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
