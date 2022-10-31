/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekantane <ekantane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 12:35:41 by ekantane          #+#    #+#             */
/*   Updated: 2022/04/27 18:49:23 by ekantane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	addline(char **str, char **line)
{
	size_t	len;
	char	*tmp;

	len = 0;
	while ((*str)[len] != '\n' && (*str)[len] != '\0')
		len++;
	if ((*str)[len] == '\n')
	{
	*line = ft_strsub(*str, 0, len);
		tmp = ft_strdup(&(*str)[len + 1]);
		free(*str);
		*str = tmp;
		if ((*str)[0] == '\0')
			ft_strdel(str);
	}
	else
	{
		*line = ft_strdup(*str);
		ft_strdel(str);
		if (len == 0)
			return (0);
	}
	return (1);
}

static int	checkflag(char **str, char **line, int ret, const int fd)
	{
	if (ret < 0)
		return (-1);
	else if (ret == 0 && str[fd] == NULL)
		return (0);
	else
		return (addline(&str[fd], line));
}

static char	*strjoinfree(char *s1, char s2[])
{
	size_t	i;
	size_t	j;
	char	*new_s;

	i = 0;
	j = 0;
	new_s = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!new_s)
		return (NULL);
	while (s1[i] != '\0')
	{
		new_s[i] = s1[i];
		i++;
	}
	while (s2[j] != '\0')
	{
		new_s[i++] = s2[j++];
	}
	new_s[i] = '\0';
	free(s1);
	return (new_s);
}

int	get_next_line(const int fd, char **line)
	{
	static char	*str[FD_SIZE];
	int			ret;
	char		*tmp;
	char		buff[BUFF_SIZE + 1];

	if (fd < 0 || !line || BUFF_SIZE <= 0 || fd > FD_SIZE)
		return (-1);
	*line = NULL;
	ft_bzero(buff, BUFF_SIZE + 1);
	ret = read(fd, buff, BUFF_SIZE);
	while (0 < ret)
	{
		if (str[fd])
		{
				tmp = strjoinfree(str[fd], buff);
				str[fd] = tmp;
		}
		else
		str[fd] = ft_strdup(buff);
		if (ft_strchr(str[fd], '\n'))
			break ;
		ft_bzero(buff, BUFF_SIZE + 1);
	ret = read(fd, buff, BUFF_SIZE);
	}
	return (checkflag(str, line, ret, fd));
}
