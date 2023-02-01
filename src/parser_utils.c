/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikarjala <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 15:43:05 by ikarjala          #+#    #+#             */
/*   Updated: 2023/02/01 17:05:02 by ikarjala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

double	parser_clamp(t_parser *p, double min, double max, double val)
{
	const char	warn[] = "value outside expected range [";

	if (val < min || val > max)
	{
		parser_warning (p, val, warn, sizeof(warn) - 1);
		ft_putnbr (min);
		write (2, " - ", 3);
		ft_putnbr (max);
		write (2, "].\n", 3);
		if (val < min)
			return (min);
		if (val > max)
			return (max);
	}
	return (val);
}

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
