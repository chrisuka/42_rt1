/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikarjala <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 15:43:05 by ikarjala          #+#    #+#             */
/*   Updated: 2023/01/30 15:52:58 by ikarjala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

/* Check whether word represents a numeric value either as
 * an integer or as a floating-point decimal number.
*/
int	is_number(char *word)
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
			return (0);
		word ++;
	}
	return (1);
}

/* Return index of where in *list* word found the first match,
 * or -1 if there wasn't one.
*/
int	word_in_list(char *word, const char **list, const size_t count)
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
