/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikarjala <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 18:58:14 by ikarjala          #+#    #+#             */
/*   Updated: 2023/01/12 16:05:43 by ikarjala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	scene_unload(t_scene *ctx)
{
	ft_memdel ((void **)(&ctx->obj));
	//ft_memdel ((void **)(&ctx->mat), ctx->mat_count);
	//ft_memdel ((void **)(&ctx->lights), ctx->light_count);
	ctx->obj_count = 0;
	ctx->light_count = 0;
	ctx->mat_count = 0;
}

static void	*lst2array(t_list *lst, const size_t unit_size, size_t count)
{
	void	*array;
	void	*ap;

	array = malloc(unit_size * count);
	if (!array)
		return (NULL);
	ap = array;
	while (count --)
	{
		ft_memmove (ap, lst->content, unit_size);
		ap += unit_size;
		lst = lst->next;
	}
	return (array);
}

void	scene_apply(t_scene *ctx, t_parser *p)
{
	ctx->obj_count = p->obj_count;
	//ctx->light_count = p->light_count;
	//ctx->mat_count = p->mat_count;
	ctx->obj = (t_obj *)lst2array(p->obj, sizeof(t_obj), p->obj_count);
#if 0
	ctx->mat = (t_mat *)lst2array(p->mat, sizeof(t_mat), p->mat_count);
	ctx->lights = (t_light *)lst2array(
		p->lights, sizeof(t_light), p->light_count);
#endif
	ft_lstdel (&p->obj, &ft_memclr);
	ft_lstdel (&p->lights, &ft_memclr);
	ft_lstdel (&p->mat, &ft_memclr);
}

