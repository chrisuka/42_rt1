# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ekantane <ekantane@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/19 01:31:36 by ikarjala          #+#    #+#              #
#    Updated: 2023/01/30 15:46:32 by ikarjala         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ROOT	:= ./
NAME	:= RTv1

SRC_DIR	:= src/
OBJ_DIR	:= obj/
INC_DIR	:= include/ libft/

CFUNC	=\
main error vector_basic vector_advanced vector_rotation color \
render render_utils raytracer intersect intersect_solve normals \
light parser parser_utils parser_tokens parser_attr parser_error scene \
get_next_line

SDL_FLAGS	:= --disable-shared --disable-video-wayland
BUILD_DIR	:= build/
SDL_CC		= $(shell $(BUILD_DIR)bin/sdl2-config --cflags)
SDL_LD		= $(shell $(BUILD_DIR)bin/sdl2-config --libs)
LIB_SDL		= $(BUILD_DIR)lib/libSDL2.a

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
$(NAME): $(PRE_REQUISITE) $(LIB_NAME) $(LIB_SDL) | $(OBJ)
	@$(ECHO) $(BMSG_LD)
	@$(LD) -o $(@) $(LDFLAGS) $(LIBRARIES) $(OBJ)
	@$(RM) $(DEP)
	@$(ECHO) $(BMSG_FIN)

-include $(DEPENDENCIES)
$(OBJ): $(OBJ_DIR)%.o:$(SRC_DIR)%.c | $(OBJ_DIR)
	@$(CC) -c $(CFLAGS) $(DEP_FLAGS) $(INCLUDE) $(SDL_CC) $(<) -o $(@)
	@$(ECHO) " $(GREEN)$(<)$(CNIL)"

$(LIB_SDL): $(BUILD_DIR)
	@cd libsdl2\
	&& ./configure --prefix=$(abspath $(BUILD_DIR)) $(SDL_FLAGS)\
	&& make && make install

$(OBJ_DIR) $(BUILD_DIR):
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
lclean:
	@$(MAKE) --directory=libft fclean
	@$(RM) -r $(BUILD_DIR)
#-- BUILD OVERRIDES -------------------|----//--||
W:	BUILD_RULES_STRICT
O:	BUILD_RULES_OPTIMAL
D:	BUILD_RULES_DEBUG
#======|============|==============================================|===========#
