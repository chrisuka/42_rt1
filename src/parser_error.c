/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikarjala <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 13:36:36 by ikarjala          #+#    #+#             */
/*   Updated: 2023/01/29 17:00:08 by ikarjala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#include "parser.h"

int	parser_exception(t_parser *p, char *word, const char *msg)
{
	const char	pre[] = EM_DEL CRED EM_PARSER EM_DEL CNIL;

	ft_putnbr_fd ((int)(p->line_num), 2);
	write (2, ",", 1);
	ft_putnbr_fd ((int)(p->word_num), 2);
	write (2, " $ ", 3);
	ft_putstr_fd (word, 2);
	write (2, pre, sizeof(pre) - 1);
	ft_panic (msg, NULL);
	return (0);
}
