/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekantane <ekantane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/31 16:24:39 by ekantane          #+#    #+#             */
/*   Updated: 2022/05/09 17:59:12 by ekantane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count_words(const char *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i] != '\0')
	{
		while (s[i] == c)
			i++;
		if (s[i] != c && s[i] != '\0')
			count++;
		while (s[i] != c && s[i] != '\0')
			i++;
	}
	return (count);
}

static int	ft_len_word(const char *s, char c)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (s[i] == c)
		i++;
	while (s[i] != c && s[i] != '\0')
	{
		len++;
		i++;
	}
	return (len);
}

static char	**fill(char const *s, char c, char **word_index, int nb_words)
{
	int	len_word;
	int	n;
	int	i;

	n = 0;
	i = 0;
	while (n < nb_words && word_index != NULL)
	{
		while (s[i] == c && word_index != NULL)
			i++;
		len_word = ft_len_word(&s[i], c);
		word_index[n] = ft_strsub(&s[i], 0, len_word);
		while (s[i] != '\0' && s[i] != c)
			i++;
		n++;
	}
	word_index[n] = NULL;
	return (word_index);
}

char	**ft_strsplit(char const *s, char c)
{
	char	**word_index;
	int		nb_words;

	if (!s || !c)
		return (NULL);
	nb_words = ft_count_words(s, c);
	word_index = (char **)malloc(sizeof(char *) * (nb_words + 1));
	if (!word_index)
		return (NULL);
	fill(s, c, word_index, nb_words);
	if (!word_index)
		return (NULL);
	else
		return (word_index);
}
