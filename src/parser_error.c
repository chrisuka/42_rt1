/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikarjala <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 13:36:36 by ikarjala          #+#    #+#             */
/*   Updated: 2023/01/21 17:11:35 by ikarjala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#include "parser.h"

int	parser_error_fatal(int ecode)
{
	const char	msg[] = CRED MPRE_PARSE "fatal error :: " CNIL;
	const char	fallback[] = "An internal fatal error occurred, aborting...";

	write (2, msg, sizeof(msg) - 1);
	if (ecode == EPARSE_INTERNAL)
		ft_putendl (strerror (errno));
	else
		ft_putendl (fallback);
	return (ecode);
}

int	parser_exception(int ecode)
{
	const char	msg[] = CRED MPRE_PARSE ":: " CNIL "unexpected token." "\n";

	write (2, msg, sizeof(msg) - 1);
	return (ecode);
}
