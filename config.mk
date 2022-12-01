# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    config.mk                                          :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ikarjala <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/18 22:41:30 by ikarjala          #+#    #+#              #
#    Updated: 2022/12/01 08:53:11 by ikarjala         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

MAKEARGS	:= --load-average=2.5 --jobs=4

ECHO 	:= echo
TOUCH	:= touch
MKDIR	:= mkdir -p
RM		:= rm -f

SRC		= $(CFUNC:%=$(SRC_DIR)%.c)
OBJ		= $(CFUNC:%=$(OBJ_DIR)%.o)
INCLUDE	= $(addprefix -I , $(INC_DIR))

CC	:= clang
LD	:= $(CC)

CFLAGS		= -Wall -Werror -Wextra $(USEFLAGS)
CFSTRICT	= -Wimplicit -Wunused -Wconversion
CFOPTIM		= -O3 -flto=full
CFDEBUG		= -g -fsanitize=address

LDFLAGS 	:= 
DEP_FLAGS	= -MMD -MP -MT $(@) -MF $(@:.o=.dep)
#=== SPECIAL ==================================================================#
.DEFAULT_GOAL	:= all
.RECIPEPREFIX	:= >
.EXTRA_PREREQS	:= 
.DELETE_ON_ERROR = $(NAME) $(OBJ)
.NOTPARALLEL: $(PRE_REQUISITE) $(OBJ_DIR)
.PHONY: norme so BUILD_RULES_STRICT BUILD_RULES_OPTIMAL BUILD_RULES_DEBUG 
#=== COMPATABILITY ============================================================#
OS	:= $(shell uname -s)
ifeq ("$(OS)" , "Linux")
ECHO := echo -e
endif
#=== COLORS ===================================================================#
ifeq ("$(COLORTERM)","truecolor")
CNIL	:=\033[0;0m
RED		:=\033[0;31m
GREEN	:=\033[0;32m
GOLD	:=\033[0;33m
BLUE	:=\033[0;34m
PURPLE	:=\033[0;35m
CYAN	:=\033[0;36m
#-BOLD-|------------|
REDB	:=\033[1;31m
GREENB	:=\033[1;32m
GOLDB	:=\033[1;33m
BLUEB	:=\033[1;34m
PURPLEB	:=\033[1;35m
CYANB	:=\033[1;36m
endif
#=== BUILD MESSAGES ===========================================================#
BMSG_FORM	:= --DEPLOY--
BMSG_PREFIX	:= $(BLUE)$(NAME)$(CNIL) :: 
BMSG_BIN	= "$(BMSG_PREFIX)$(CYANB)Starting $(BMSG_FORM) build$(CNIL)..."
BMSG_CC		= "$(BMSG_PREFIX)$(CNIL)$(CC) $(CFLAGS)"
BMSG_LD		= "$(BMSG_PREFIX)$(PURPLEB)Linking:$(CNIL) $(LIBS)"
BMSG_FIN	= "$(BMSG_PREFIX)$(GREENB)Build success!$(CNIL)"
#=== UTILITIES ================================================================#
CMD_NORME		:= norminette -R CheckForbiddenSourceHeader
PRE_REQUISITE	:= .buildinfo
$(PRE_REQUISITE):
	@$(ECHO)	$(BMSG_BIN)
	@$(ECHO)	$(BMSG_CC)
	@$(TOUCH)	$(PRE_REQUISITE)
norme: $(SRC_DIR) $(INC_DIR)
	@$(CMD_NORME) $(<)
#=== BUILD OVERRIDES ==========================================================#
BUILD_RULES_STRICT:		BMSG_FORM := --STRICT--
BUILD_RULES_STRICT:		CFLAGS += $(CFSTRICT)
BUILD_RULES_STRICT:		re
BUILD_RULES_OPTIMAL:	BMSG_FORM := --OPTIMIZED--
BUILD_RULES_OPTIMAL: 	CFLAGS += $(CFOPTIM)
BUILD_RULES_OPTIMAL: 	re
BUILD_RULES_DEBUG:		BMSG_FORM := --DEBUG--
BUILD_RULES_DEBUG:		CFLAGS += $(CFDEBUG)
BUILD_RULES_DEBUG:		re
#======|============|==========================================================#
