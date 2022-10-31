/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekantane <ekantane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 14:49:15 by ekantane          #+#    #+#             */
/*   Updated: 2022/04/27 18:53:58 by ekantane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include "libft.h"
# define FD_SIZE 4096
# define BUFF_SIZE 11000

# include <stdlib.h>
# include <unistd.h>
# include <string.h>

int	get_next_line(const int fd, char **line);

#endif
