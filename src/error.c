/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikarjala <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 17:45:23 by ikarjala          #+#    #+#             */
/*   Updated: 2022/11/20 20:00:31 by ikarjala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

/* Write a message to STDERROR, optionally call a function and return -1.
 * This function can be i.e. something that frees all malloced program data.
 * Intended for easy "panic" shutdowns of the program in case of internal error.
*/
int	ft_panic(const char *msg, void (*hook)(void))
{
	ft_putendl_fd (msg, 2);
	if (hook)
		hook ();
	return (-1);
}
