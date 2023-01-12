/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikarjala <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 13:36:36 by ikarjala          #+#    #+#             */
/*   Updated: 2023/01/11 14:25:24 by ikarjala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#include "parser.h"

int	parser_error_fatal(int ecode)
{
	const char	msg[] = CRED MPRE_PARSE "fatal error :: " CNIL;

	write (2, msg, sizeof(msg) - 1);
	//ft_putendl (strerror());
	ft_putnbr (ecode);
	ft_putendl ("unable to open file.");
	return (ecode);
}

int	parser_exception(int ecode)
{
	const char	msg[] = CRED MPRE_PARSE " :: " CNIL "unexpected token." "\n";

	write (2, msg, sizeof(msg) - 1);
	return (ecode);
}
