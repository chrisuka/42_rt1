/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_attr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikarjala <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 13:01:44 by ikarjala          #+#    #+#             */
/*   Updated: 2023/01/21 17:58:50 by ikarjala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

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
		{
			// error
			return (0);
		}
		word ++;
	}
	return (1);
}

static inline int	set_attr_meta(t_parser *p, t_tuple av3)
{
	if (p->attr.type == ATTRIX_POSITION)
	{
		p->cam.pos = av3.v3;
		ft_putendl ("set cam position");
	}
	else if (p->attr.type == ATTRIX_ROTATION)
	{
		p->cam.rot = av3.v3;
		ft_putendl ("set cam rotation");
	}
	else if (p->attr.type == ATTRIX_AMBIENT)
	{
		p->ambient = av3.v3.z;
		ft_putendl ("set ambient");
	}
	return (EPARSE_OK);
}

static inline int	set_attr_material(t_parser *p, t_tuple av3)
{
	t_mat	*mat;

	if (!p->mat || !p->mat->content)
		return (parser_error_fatal (EPARSE_INTERNAL));
	mat = (t_mat *)(p->mat->content);
	if (p->attr.type == ATTRIX_COLOR)
	{
		av3.rgb = (t_rgbf){fmin (1.0L, av3.rgb.r), fmin (1.0L, av3.rgb.g), fmin (1.0L, av3.rgb.b)};
		mat->color = av3.rgb;
		ft_putendl ("set material color");
	}
	else if (p->attr.type == ATTRIX_GLOSS)
	{
		mat->gloss = av3.v3.z;
		ft_putendl ("set material gloss");
	}
	else if (p->attr.type == ATTRIX_SPECULAR)
	{
		mat->specular = av3.v3.z;
		ft_putendl ("set material specular");
	}
	return (EPARSE_OK);
}

static inline int	set_attr_light(t_parser *p, t_tuple av3)
{
	t_light	*light;

	if (!p->lights || !p->lights->content)
		return (parser_error_fatal (EPARSE_INTERNAL));
	light = (t_light *)(p->lights->content);
	if (p->attr.type == ATTRIX_POSITION)
	{
		light->pos = av3.v3;
		ft_putendl ("set light position");
	}
	else if (p->attr.type == ATTRIX_INTENSITY)
	{
		light->intensity = av3.v3.z;
		ft_putendl ("set light intensity");
	}
	return (EPARSE_OK);
}

static inline int	set_attr_obj(t_parser *p, t_tuple av3)
{
	t_obj	*obj;

	if (!p->obj || !p->obj->content)
		return (parser_error_fatal (EPARSE_INTERNAL));
	obj = (t_obj *)(p->obj->content);
	if (p->attr.type == ATTRIX_POSITION)
	{
		obj->pos = av3.v3;
		ft_putendl ("set obj position");
	}
	else if (p->attr.type == ATTRIX_ROTATION)
	{
		obj->rot = av3.v3;
		ft_putendl ("set obj rotation");
	}
	else if (p->attr.type == ATTRIX_RADIUS)
	{
		obj->r = av3.v3.z;
		ft_putendl ("set obj radius");
	}
	else if (p->attr.type == ATTRIX_MATERIALP)
	{
		if ((size_t)(av3.v3.z) >= p->mat_count)
			return (parser_exception (EPARSE_MATERIAL_INDEX));
		ft_putendl ("set obj material");
		obj->mat = (int)(av3.v3.z);
	}
	return (EPARSE_OK);
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
	{
		ft_putendl ("NaN");
		return (parser_exception (EPARSE_TOKEN_NAN));
	}
	p->av[p->attr.val_req] = ft_atof(word);
	if (p->attr.val_req != 0)
		return (1);
	av3.v3 = (t_vec){.x = p->av[2], .y = p->av[1], .z = p->av[0]};
	if (p->active_type < 0 || p->active_type >= (int)(sizeof(jmp) / sizeof(jmp[0])))
		return (parser_exception (EPARSE_TOKEN_INVALID));
	jmp [p->active_type](p, av3);
	return (1);
}
