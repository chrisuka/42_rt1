/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikarjala <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 15:25:48 by ikarjala          #+#    #+#             */
/*   Updated: 2023/01/21 17:54:29 by ikarjala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static int	word_in_list(char *word, const char **list, const size_t count)
{
	int	n;

	n = -1;
	while (++n < (int)(count))
	{
		if (ft_strequ (word, (char *)(list[n])))
			return (n);
	}
	return (-1);
}

int	token_try_attr(char *word, t_parser *p)
{
	const char	*keyws[] = {"pos", "rot", "radius", "matp",
		"intensity", "color", "gloss", "specular"};
	const int	valreqs[] = {3, 3, 1, 1, 1, 3, 1, 1};
	int			n;

	n = word_in_list (word, keyws, sizeof(keyws) / sizeof(keyws[0]));
	if (n == -1)
		return (0);
	if (!(p->active_type == tobj ||
		p->active_type == tlight ||
		p->active_type == tmaterial ||
		p->active_type == tmeta)
			|| p->attr.val_req != 0)
		return (parser_exception (EPARSE_TOKEN_INVALID));
	p->attr = (t_attr){.type = n, .val_req = valreqs[n]};
	ft_bzero ((void *)(p->av), sizeof(p->av));
	return (1);
}

int	token_try_light(char *word, t_parser *p)
{
	t_list		*node;

	if (!ft_strequ (word, "light"))
		return (0);
	node = p->lights;
	p->lights = (t_list *)malloc(sizeof(t_list)); // TODO: ft_lstpush (insert at beginning)
	p->lights->content = (void *)malloc(sizeof(t_light));
	p->lights->content_size = sizeof(t_light);
	p->lights->next = node;
	p->light_count ++;
	p->active_type = tlight;
	return (1);
}

static inline t_obj	*obj_init(int id)
{
	t_obj	*obj;

	obj = (t_obj *)malloc(sizeof(t_obj));
	if (obj)
		*obj = (t_obj){.id = id,
			.pos = (t_vec){0, 0, 0}, .rot = (t_vec){0, 1, 0}, .r = 2,
			.mat = -1
		};
	return (obj);
}
int	token_try_meta(char *word, t_parser *p)
{
	if (ft_strequ (word, "cam"))
		p->attr = (t_attr){.type = -1};
	else if (ft_strequ (word, "ambient"))
	{
		p->attr = (t_attr){.type = ATTRIX_AMBIENT, .val_req = 1};
		ft_bzero ((void *)(p->av), sizeof(p->av));
	}
	else
		return (0);
	p->active_type = tmeta;
	return (1);
}

int	token_try_material(char *word, t_parser *p)
{
	t_list		*node;

	if (!ft_strequ (word, "material"))
		return (0);
	node = p->mat;
	p->mat = (t_list *)malloc(sizeof(t_list)); // TODO: ft_lstpush (insert at beginning)
	p->mat->content = (void *)malloc(sizeof(t_mat));
	// if !ft_lstpush
	if (!p->mat->content)
		return (parser_error_fatal (EPARSE_INTERNAL));
	p->mat->content_size = sizeof(t_mat);
	p->mat->next = node;
	p->mat_count ++;
	p->active_type = tmaterial;
	*((t_mat *)(p->mat->content)) = (t_mat){
		.color = (t_rgbf){1, 1, 1}, .gloss = 1.0, .specular = 0.0};
	return (1);
}

int	token_try_obj(char *word, t_parser *p)
{
	const char	*keyws[] = {"sphere", "cylinder", "cone", "plane"};
	t_list		*node;
	int			n;

	n = word_in_list (word, keyws, sizeof(keyws) / sizeof(keyws[0]));
	if (n == -1)
		return (0);
	node = p->obj;
	p->obj = (t_list *)malloc(sizeof(t_list)); // TODO: ft_lstpush (insert at beginning)
	p->obj->content = (void *)obj_init(n);
	p->obj->content_size = sizeof(t_obj);
	p->obj->next = node;
	p->obj_count ++;
	p->active_type = tobj;
	return (1);
}
