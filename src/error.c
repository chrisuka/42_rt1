/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikarjala <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 17:45:23 by ikarjala          #+#    #+#             */
/*   Updated: 2023/01/25 20:17:31 by ikarjala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

/* Write a message to STDERROR, optionally call a function and exit.
 * This function can be i.e. something that frees all malloced program data.
 * Intended for easy "panic" shutdowns of the program in case of internal error.
*/
int	ft_panic(const char *msg, void (*hook)(void))
{
	const char post[] = "Aborting ..." "\n";

	ft_putendl_fd (msg, 2);
	if (hook)
		hook ();
	write (2, post, sizeof(post) - 1);
	exit (-1);
	return (0);
}
