/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikarjala <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 15:25:48 by ikarjala          #+#    #+#             */
/*   Updated: 2023/01/20 17:32:12 by ikarjala         ###   ########.fr       */
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

// v=============== UNFINISHED ===============v //
#if 1
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

#include <stdio.h>
int	set_attr (char *word, t_parser *p)
{
	t_tuple	av3;
	t_obj	*obj;
	t_light	*light;
	t_mat	*mat;

	if (p->obj)
		obj = (t_obj *)(p->obj->content);
	if (p->lights)
		light = (t_light *)(p->lights->content);
	if (p->mat)
		mat = (t_mat *)(p->mat->content);

	p->attr.val_req --;
	if (!is_number (word))
	{
		ft_putendl ("NaN");
		return (parser_exception (EPARSE_TOKEN_NAN));
	}
	p->av[p->attr.val_req] = ft_atof(word);
	av3.v3 = (t_vec){.x = p->av[2], .y = p->av[1], .z = p->av[0]};
	printf ("set value to %lf\n", p->av[p->attr.val_req]); //DEBUG
	if (p->attr.val_req != 0)
		return (1);
#if 1
	//if (p->attr.type == obj)
	// TODO: check that attr type matches obj/mat/light/meta
	if (p->active_type == tobj)
	{
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
	}
	else if (p->active_type == tlight)
	{
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
	}
	else if (p->active_type == tmaterial)
	{
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
		
	}
	else if (p->active_type == tmeta)
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
	}
	else
		return (parser_exception (EPARSE_TOKEN_INVALID));
#endif
	return (1);
}
#endif

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
// ^=============== UNFINISHED ===============^ //

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
