/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikarjala <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 15:25:48 by ikarjala          #+#    #+#             */
/*   Updated: 2023/01/25 20:45:13 by ikarjala         ###   ########.fr       */
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
	if (!(p->active_type == tobj
			|| p->active_type == tlight
			|| p->active_type == tmaterial
			|| p->active_type == tmeta)
		|| p->attr.val_req != 0)
		return (parser_exception (p, word, MEPARSE_BADCONTEXT));
	p->attr = (t_attr){.type = n, .val_req = valreqs[n]};
	ft_bzero ((void *)(p->av), sizeof(p->av));
	return (1);
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

int	token_try_light(char *word, t_parser *p)
{
	t_light	*light;

	if (!ft_strequ (word, "light"))
		return (0);
	light = (t_light *)malloc(sizeof(t_light));
	if (!light || !ft_lstenque (&p->lights, light, sizeof(t_light)))
		return (parser_exception (p, word, EM_INTERNAL));
	p->light_count ++;
	p->active_type = tlight;
	return (1);
}

int	token_try_material(char *word, t_parser *p)
{
	t_mat	*mat;

	if (!ft_strequ (word, "material"))
		return (0);
	mat = (t_mat *)malloc(sizeof(t_mat));
	if (!mat || !ft_lstenque (&p->mat, mat, sizeof(t_mat)))
		return (parser_exception (p, word, EM_INTERNAL));
	p->mat_count ++;
	p->active_type = tmaterial;
	*mat = (t_mat){
		.color = (t_rgbf){1, 1, 1}, .gloss = 1.0, .specular = 0.0};
	return (1);
}

int	token_try_obj(char *word, t_parser *p)
{
	const char	*keyws[] = {"sphere", "cylinder", "cone", "plane"};
	int			type;
	t_obj		*obj;

	type = word_in_list (word, keyws, sizeof(keyws) / sizeof(keyws[0]));
	if (type == -1)
		return (0);
	obj = (t_obj *)malloc(sizeof(t_obj));
	if (!obj || !ft_lstenque (&p->obj, obj, sizeof(t_obj)))
		return (parser_exception (p, word, EM_INTERNAL));
	p->obj_count ++;
	p->active_type = tobj;
	*obj = (t_obj){
		.id = type, .r = 2, .mat = -1,
		.pos = (t_vec){0, 0, 0}, .rot = (t_vec){0, 1, 0},
	};
	return (1);
}
