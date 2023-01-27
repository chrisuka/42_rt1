/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_attr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikarjala <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 13:01:44 by ikarjala          #+#    #+#             */
/*   Updated: 2023/01/27 18:43:35 by ikarjala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

/* Check whether word represents a numeric value either as
 * an integer or as a floating-point decimal number.
*/
static inline int	is_number(char *word)
{
	const int	neg = word[0] == '-';
	int			dec;

	dec = 0;
	word += neg;
	while (*word)
	{
		if (ft_isdigit (*word))
			;
		else if (*word == '.' && !dec)
			dec = 1;
		else
			return (0);
		word ++;
	}
	return (1);
}

static inline int	set_attr_meta(t_parser *p, t_tuple av3)
{
	if (p->attr.type == ATTRIX_POSITION)
		p->cam.pos = av3.v3;
	else if (p->attr.type == ATTRIX_ROTATION)
		p->cam.rot = av3.v3;
	else if (p->attr.type == ATTRIX_AMBIENT)
		p->ambient = av3.v3.z;
	return (0);
}

static inline int	set_attr_material(t_parser *p, t_tuple av3)
{
	t_mat	*mat;

	if (!p->mat || !p->mat->content)
		return (parser_exception (p, NULL, EM_INTERNAL));
	mat = (t_mat *)(p->mat->content);
	if (p->attr.type == ATTRIX_COLOR)
	{
		av3.rgb = (t_rgbf){
			fmax (0.0L, fmin (1.0L, av3.rgb.r)),
			fmax (0.0L, fmin (1.0L, av3.rgb.g)),
			fmax (0.0L, fmin (1.0L, av3.rgb.b))};
		mat->color = av3.rgb;
	}
	else if (p->attr.type == ATTRIX_GLOSS)
		mat->gloss = fmax (0.0L, av3.v3.z);
	else if (p->attr.type == ATTRIX_SPECULAR)
		mat->specular = fmax (0.0L, av3.v3.z);
	return (0);
}

static inline int	set_attr_light(t_parser *p, t_tuple av3)
{
	t_light	*light;

	if (!p->lights || !p->lights->content)
		return (parser_exception (p, NULL, EM_INTERNAL));
	light = (t_light *)(p->lights->content);
	if (p->attr.type == ATTRIX_POSITION)
		light->pos = av3.v3;
	else if (p->attr.type == ATTRIX_INTENSITY)
		light->intensity = av3.v3.z;
	return (0);
}

static inline int	set_attr_obj(t_parser *p, t_tuple av3)
{
	t_obj	*obj;

	if (!p->obj || !p->obj->content)
		return (parser_exception (p, NULL, EM_INTERNAL));
	obj = (t_obj *)(p->obj->content);
	if (p->attr.type == ATTRIX_POSITION)
		obj->pos = av3.v3;
	else if (p->attr.type == ATTRIX_ROTATION)
		obj->rot = vec_rot ((t_vec){0, 1, 0}, av3.v3);
	else if (p->attr.type == ATTRIX_RADIUS)
		obj->r = fmax (0.0L, av3.v3.z);
	else if (p->attr.type == ATTRIX_MATERIALP)
	{
		if ((size_t)(av3.v3.z) >= p->mat_count)
			return (parser_exception (p, NULL, MEPARSE_MATP));
		obj->mat = (int)(av3.v3.z);
	}
	return (0);
}

int	set_attr(char *word, t_parser *p)
{
	t_tuple					av3;
	const t_attr_dispatch	jmp[] = {
		set_attr_obj,
		set_attr_light,
		set_attr_material,
		set_attr_meta
	};

	p->attr.val_req --;
	if (!is_number (word))
		return (parser_exception (p, word, MEPARSE_NAN));
	p->av[p->attr.val_req] = ft_atof(word);
	if (p->attr.val_req != 0)
		return (1);
	av3.v3 = (t_vec){.x = p->av[2], .y = p->av[1], .z = p->av[0]};
	if (p->active_type < 0 || p->active_type >= (int)(sizeof(jmp) / sizeof(jmp[0])))
		return (parser_exception (p, word, MEPARSE_BADCONTEXT));
	jmp [p->active_type](p, av3);
	return (1);
}
