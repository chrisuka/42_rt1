/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikarjala <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 15:25:48 by ikarjala          #+#    #+#             */
/*   Updated: 2023/01/17 19:17:46 by ikarjala         ###   ########.fr       */
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

int	set_attr (char *word, t_parser *p)
{
	t_vec	av3;
#if 1
	t_obj	*obj;
	t_light	*light;
	//t_mat	*mat;

	if (p->obj)
		obj = (t_obj *)(p->obj->content);
	if (p->lights)
		light = (t_light *)(p->lights->content);
	//mat = (t_mat *)(p->mat->content);
#endif

	p->attr.val_req --;
	if (!is_number (word))
	{
		ft_putendl ("NaN");
		return (parser_exception (EPARSE_TOKEN_NAN));
	}
	p->av[p->attr.val_req] = ft_atoi(word);
	av3 = (t_vec){.x = p->av[2], .y = p->av[1], .z = p->av[0]};
#if 1
	//if (p->attr.type == obj)
	// TODO: check that attr type matches obj/mat/light/meta
	if (p->active_type == tobj)
	{
		if (p->attr.type == 0)
		{
			obj->pos = av3;
			ft_putendl ("set obj position");
		}
		else if (p->attr.type == 1)
		{
			obj->rot = av3;
			ft_putendl ("set obj rotation");
		}
		else if (p->attr.type == 2)
		{
			obj->r = av3.z;
			ft_putendl ("set obj radius");
		}
	}
	else if (p->active_type == tlight)
	{
		if (p->attr.type == 0)
		{
			light->pos = av3;
			ft_putendl ("set light position");
		}
		else if (p->attr.type == 1)
		{
			light->intensity = av3.z;
			ft_putendl ("set light rotation");
		}
	}
	else if (p->active_type == tmaterial)
	{
	}
	else if (p->active_type == tmeta)
	{
	}
	else
		return (parser_exception (EPARSE_TOKEN_INVALID));
#endif
	return (1);
}
#endif

int	token_try_attr(char *word, t_parser *p)
{
	const char	*keyws[] = {"pos", "rot", "radius", "matp"};
	const int	valreqs[] = {3, 3, 1, 1};
	int			n;

	n = word_in_list (word, keyws, sizeof(keyws) / sizeof(keyws[0]));
	if (n == -1)
		return (0);
	if (!(p->active_type == tobj ||
		p->active_type == tlight ||
		p->active_type == tmaterial))
		return (parser_exception (EPARSE_TOKEN_INVALID));
	p->attr = (t_attr){.type = n, .val_req = valreqs[n]};
	bzero ((void *)(p->av), sizeof(p->av));
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

static inline t_obj	*obj_init(int id, t_mat *mat)
{
	t_obj	*obj;

	obj = (t_obj *)malloc(sizeof(t_obj));
	if (obj)
		*obj = (t_obj){.id = id,
			.pos = (t_vec){0, 0, 0}, .rot = (t_vec){0, 1, 0}, .r = 2,
			.mat = mat
		};
	return (obj);
}

int	token_try_obj(char *word, t_parser *p)
{
	const char	*keyws[] = {"sphere", "cylinder", "cone", "plane"};
	t_list		*node;
	int			n;

	n = word_in_list (word, keyws, sizeof(keyws) / sizeof(keyws[0]));
	if (n == -1)
		return (0);
#if 1
	node = p->obj;
	p->obj = (t_list *)malloc(sizeof(t_list)); // TODO: ft_lstpush (insert at beginning)
	p->obj->content = (void *)obj_init(n, p->default_matp);
	p->obj->content_size = sizeof(t_obj);
	p->obj->next = node;
	p->obj_count ++;
	p->active_type = tobj;
#endif
	p = NULL; // to shut the compiler up
	return (1);
}
