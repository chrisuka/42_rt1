# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    sdl.mk                                             :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ekantane <ekantane@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/02 17:34:53 by ekantane          #+#    #+#              #
#    Updated: 2023/02/02 17:37:03 by ekantane         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SDL_INCLUDE	=	-I./frameworks/SDL2.framework/Versions/A/Headers \
				-I./frameworks/SDL2_image.framework/Versions/A/Headers \
				-I./frameworks/SDL2_mixer.framework/Versions/A/Headers \
				-F./frameworks/

FRAMEWORKS	=	-F./frameworks \
				-rpath ./frameworks \
				-framework SDL2 -framework SDL2_image \
				-framework SDL2_mixer
