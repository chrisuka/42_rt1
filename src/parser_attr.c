/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_attr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikarjala <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 13:01:44 by ikarjala          #+#    #+#             */
/*   Updated: 2023/01/09 14:47:58 by ikarjala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int	check_token_meta(char *word)
{
	if (ft_strequ (word, "cam"))
		p->arg_type = meta_cam;
	else if (ft_strequ (word, "ambient"))
		p->arg_type = meta_attr;
}

int	check_token_attr(char *word)
{
	const char		*av[] = {"pos", "rot", "radius"};
	const int		avr[] = {3, 3, 1};
	const size_t	count = sizeof(av) / sizeof(av[0]);
	int				n;

	if (p->arg_type == null)
		return (parser_exception (EPARSE_TOKEN_INVALID));
	n = word_in_list (word, av, count);
	if (n == -1)
		return (parser_exception (EPARSE_TOKEN_INVALID));
	p->attr_val_req = avr[n];
	return (1);
}

// TODO: account for attrs for different types: obj, meta_cam, meta_attr, light, material
