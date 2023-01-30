/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekantane <ekantane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 18:58:14 by ikarjala          #+#    #+#             */
/*   Updated: 2023/01/30 15:40:56 by ikarjala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_scene	scene_init(void)
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

void	scene_unload(t_scene *ctx)
{
	ft_memdel ((void **)(&ctx->obj));
	ft_memdel ((void **)(&ctx->lights));
	ft_memdel ((void **)(&ctx->mat));
	ctx->obj_count = 0;
	ctx->light_count = 0;
	ctx->mat_count = 0;
}

/* Create an array of *count* arbitrary objects from a list of objects
 * of *unit_size*. In this context the list has been initialized
 * First-In-Last-Out, meaning in reverse order to the parsed file.
 * Therefore, we should populate the array in reverse order.
*/
static void	*lst2array(t_list *lst, const size_t unit_size, size_t count)
{
	void	*array;
	void	*ap;

	if (!unit_size || !count)
		return (NULL);
	array = tense_malloc(unit_size * count);
	if (!array)
		return (NULL);
	ap = array + unit_size * count;
	while (count --)
	{
		ap -= unit_size;
		ft_memmove (ap, lst->content, unit_size);
		lst = lst->next;
	}
	return (array);
}

/* Transfer parser data to construct the scene context
 * and unload the parser.
*/
void	scene_apply(t_scene *ctx, t_parser *p)
{
	ctx->cam = p->cam;
	ctx->ambient = p->ambient;
	ctx->obj_count = p->obj_count;
	ctx->obj = (t_obj *)lst2array(p->obj, sizeof(t_obj), p->obj_count);
	ctx->light_count = p->light_count;
	ctx->lights = (t_light *)lst2array(
			p->lights, sizeof(t_light), p->light_count);
	ctx->mat_count = p->mat_count;
	ctx->mat = (t_mat *)lst2array(p->mat, sizeof(t_mat), p->mat_count);
	ft_lstdel (&p->obj, &ft_memclr);
	ft_lstdel (&p->lights, &ft_memclr);
	ft_lstdel (&p->mat, &ft_memclr);
}
