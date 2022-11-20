# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ikarjala <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/19 01:31:36 by ikarjala          #+#    #+#              #
#    Updated: 2022/11/20 19:44:00 by ikarjala         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ROOT	:= ./
NAME	:= RTv1

SRC_DIR	:= src/
OBJ_DIR	:= obj/
INC_DIR	:= include/ libft/

CFUNC	=\
main vector color render_utils parser error

SDL_DIR		:= build/libsdl2/
SDL_CC		:= $(shell $(SDL_DIR)bin/sdl2-config --cflags)
SDL_LD		:= $(shell $(SDL_DIR)bin/sdl2-config --libs)

LIB_NAME	= libft/libft.a
LIBRARIES	= $(LIB_NAME) $(SDL_LD)

DEPENDENCIES	= $(OBJ:.o=.dep)

SUBMAKES = config.mk
include $(SUBMAKES)
#=== SPECIAL ==================================================================#
.DEFAULT_GOAL	:= all
.PHONY: all clean fclean re
#=== TARGETS ==================================================================#
all: $(NAME)
$(NAME): CFLAGS += $(SDL_CFLAGS)
$(NAME): $(PRE_REQUISITE) Makefile | $(LIB_NAME) $(OBJ)
	@$(ECHO) $(BMSG_LD)
	@$(LD) -o $(@) $(LDFLAGS) $(LIBRARIES) $(OBJ)
	@$(RM) $(DEP)
	@$(ECHO) $(BMSG_FIN)

-include $(DEPENDENCIES)
$(OBJ): $(OBJ_DIR)%.o:$(SRC_DIR)%.c | $(OBJ_DIR)
	@$(CC) -c $(CFLAGS) $(DEP_FLAGS) $(INCLUDE) $(SDL_CC) $(<) -o $(@)
	@$(ECHO) " $(GREEN)$(<)$(CNIL)"

$(OBJ_DIR):
	@$(MKDIR) $(@)
	
$(LIB_NAME):
	@$(MAKE) --directory=$(@D) $(MAKEFLAGS) $(MAKEARGS) all
#-- CLEANUP ---------------------------|----//--||
clean:
	@$(ECHO)	"Cleaning objects..."
	@$(RM)		$(OBJ) $(DEPENDENCIES) $(PRE_REQUISITE)
	@$(RM) -d	$(OBJ_DIR)
fclean: clean
	@$(ECHO)	"Removing binaries..."
	@$(RM) $(NAME) $(NAME:.a=.so)
re: fclean all
#-- OVERRIDES -------------------------|----//--||
W:		strict
strict:	BMSG_FORM := --STRICT--
strict:	CFLAGS += $(CFSTRICT)
strict:	re

O:		optim
optim:	BMSG_FORM := --OPTIMIZED--
optim: 	CFLAGS += $(CFOPTIM)
optim: 	re

d:		debug
debug:	BMSG_FORM := --DEBUG--
debug:	CFLAGS += $(CFDEBUG)
debug:	re
#======|============|==============================================|===========#
