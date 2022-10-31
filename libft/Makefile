# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ekantane <ekantane@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/30 19:20:27 by ekantane          #+#    #+#              #
#    Updated: 2022/04/27 18:53:11 by ekantane         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

CC = gcc

SRCS			=	ft_isalnum.c ft_isprint.c ft_memcmp.c ft_strcat.c ft_strcmp.c \
					ft_strlcat.c ft_strncmp.c ft_atoi.c ft_isalpha.c ft_strcpy.c \
					ft_memcpy.c  ft_strchr.c ft_bzero.c ft_strncat.c ft_strstr.c \
					ft_strnstr.c ft_tolower.c ft_bzero.c ft_isascii.c ft_memccpy.c \
					ft_memmove.c ft_strdup.c ft_strlen.c ft_strrchr.c ft_strncpy.c \
					ft_toupper.c ft_isdigit.c ft_memchr.c ft_memset.c ft_memalloc.c \
					ft_memdel.c ft_strnew.c ft_strdel.c ft_strclr.c ft_striter.c \
					ft_striteri.c ft_strmap.c ft_strmapi.c ft_strequ.c ft_strnequ.c \
					ft_strsub.c ft_strjoin.c ft_strtrim.c ft_strsplit.c ft_itoa.c \
					ft_putchar.c ft_putstr.c ft_putendl.c ft_putnbr.c ft_putchar_fd.c \
					ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_lstadd.c \
					ft_lstdel.c ft_lstdelone.c ft_lstiter.c ft_lstmap.c ft_lstnew.c \
					ft_strspn.c ft_strndup.c ft_intlower.c ft_inthigher.c \
					get_next_line.c

OBJ = *.o

FLAGS = -Wall -Wextra -Werror

all:	$(NAME)

$(NAME):
	$(CC) -c $(SRCS) $(FLAGS) -I $(HEADER)
	ar rc $(NAME) $(OBJ)
	ranlib $(NAME)

clean:
	rm -rf $(OBJ)
	
fclean: clean
	rm -rf $(NAME)
	
re: fclean all
