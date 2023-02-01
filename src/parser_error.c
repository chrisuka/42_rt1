/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikarjala <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 13:36:36 by ikarjala          #+#    #+#             */
/*   Updated: 2023/02/01 17:29:42 by ikarjala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#include "parser.h"

int	parser_warning(t_parser *p, double val, const char *msg, const size_t len)
{
	const char	pre[] = EM_DEL CGOLD WM_PARSER EM_DEL CNIL;

	ft_putnbr_fd ((int)(p->line_num), 2);
	write (2, ",", 1);
	ft_putnbr_fd ((int)(p->word_num), 2);
	write (2, " $ ~", 4);
	ft_putnbr_fd (val, 2);
	write (2, pre, sizeof(pre) - 1);
	write (2, msg, len);
	return (0);
}

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
