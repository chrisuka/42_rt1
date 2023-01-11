# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ikarjala <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/19 01:31:36 by ikarjala          #+#    #+#              #
#    Updated: 2023/01/11 17:07:02 by ikarjala         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ROOT	:= ./
NAME	:= libft.a
SO		:= $(NAME:.a=.so)

SRC_DIR	:= src/
OBJ_DIR	:= obj/
INC_DIR	:= ./

MANDATORY_FILES =\
isdigit isalpha isalnum isascii isprint tolower toupper itoa atoi \
strlen strcmp strncmp strequ strnequ \
strchr strrchr strstr strnstr \
\
strcpy strncpy strcat strncat strlcat striter striteri \
strnew strdup strsub strtrim strmap strmapi strjoin strsplit \
strclr strdel \
\
bzero memset memchr memcmp memcpy memccpy memmove mapi \
memalloc memdup memdel memclr \
\
putchar putchar_fd putstr putstr_fd putendl putendl_fd \
putnbr putnbr_fd
BONUS_FILES =\
lstnew lstadd lstdelone lstdel lstiter lstmap
EXTRA_FILES =\
islower isupper isspace isxdigit toinverse \
bool2sign abs log10 pow min max utoa64 \
strany swap strword wordcount \
aiter freearray bset64 \
lstlen lstn lstclen lstinit lstcut lstbuflen lststr
CSTAGE	= $(MANDATORY_FILES) $(BONUS_FILES) $(EXTRA_FILES)
CFUNC	= $(CSTAGE:%=ft_%)

SUBMAKES = config.mk
include $(SUBMAKES)
#=== SPECIAL ==================================================================#
.DEFAULT_GOAL	:= all
.PHONY: all clean fclean re
#=== TARGETS ==================================================================#
all: $(NAME) $(SO)
$(NAME): $(PRE_REQUISITE) $(OBJ_DIR) $(OBJ)
	@$(ECHO);$(ECHO) $(BMSG_LD)
	@$(LD) $(LDFLAGS) $(@) $(OBJ)
	@$(ECHO) $(BMSG_FIN)
$(SO):

$(OBJ): $(OBJ_DIR)%.o:$(SRC_DIR)%.c
	@$(CC) -c $(CFLAGS) $(INCLUDE) $(<) -o $(@)
	@$(ECHO) -n "[$(GREEN)$(<)$(CNIL)]"

$(OBJ_DIR):
	@$(MKDIR) $(@)
#-- CLEANUP ---------------------------|----//--||
clean:
	@$(ECHO) "$(RED)$(OBJ)$(CNIL)"
	@$(RM)		$(OBJ) $(DEPENDENCIES) $(PRE_REQUISITE)
	@$(RM) -d	$(OBJ_DIR)
fclean: clean
	@$(ECHO) "$(RED)$(NAME) $(SO)$(CNIL)"
	@$(RM)		$(NAME) $(SO)
	@$(ECHO) "$(GREEN)Mm, refreshing!$(CNIL)"
re: fclean all
#-- BUILD OVERRIDES -------------------|----//--||
.PHONY: W O D .WAIT
W:	BUILD_RULES_STRICT
O:	BUILD_RULES_OPTIMAL
D:	BUILD_RULES_DEBUG
#======|============|==============================================|===========#
