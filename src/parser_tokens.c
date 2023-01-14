/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikarjala <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 15:25:48 by ikarjala          #+#    #+#             */
/*   Updated: 2023/01/14 16:09:03 by ikarjala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

// v=============== UNFINISHED ===============v //
#if 0
int	check_token_num(char *word)
{
	const int	neg = word[0] == '-';
	int			dec;

	dec = 0;
	word += neg;
	while (*word)
	{
		if (ft_isdigit (*word))
			continue ; // word ++;
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
	if (!check_token_num (word))
		return (parser_exception (EPARSE_TOKEN_UNKNOWN));
	if (!p->attrp)
		return (parser_exception (EPARSE_TOKEN_INVALID));
	if (p->active_type == obj)
		((t_vec *)(p->attrp))
			// TODO: need to add type for current attr as well
	p->attr_val_req --;
}

int	token_try_attr(char *word, t_parser *p)
{
	const char	*keyws[] = {"pos", "euler", "radius","material"};
	int			n;

	n = word_in_list (word, keyws, sizeof(keyws) / sizeof(keyws[0]));
	if (n == -1)
		return (0);
	if (p->active_type == -1)
		return (parser_exception (EPARSE_TOKEN_INVALID));
	// NOTE: needs to account for materials/lights/cam/ambient as well
	else if (n == 0)
		p->attrp = (void *)(((t_obj *)(p->current_node))->pos);
	else if (n == 1)
		p->attrp = ((t_obj *)(p->current_node))->rot;
	else if (n == 2)
		p->attrp = ((t_obj *)(p->current_node))->r;
	return (1);
}
#endif
// ^=============== UNFINISHED ===============^ //

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

int	token_try_light(char *word, t_parser *p)
{
	const char	keyw[] = "light";
	t_list		*node;

	if (!ft_strequ (word, keyw))
		return (0);
	node = p->lights;
	p->lights = (t_list *)malloc(sizeof(t_list)); // TODO: ft_lstpush (insert at beginning)
	p->lights->content = (void *)malloc(sizeof(t_light));
	p->lights->content_size = sizeof(t_light);
	p->lights->next = node;
	p->light_count ++;
	//p->active_type = light;
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
	//p->active_type = obj;
#endif
	p = NULL; // to shut the compiler up
	return (1);
}
