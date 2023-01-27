/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekantane <ekantane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 14:19:38 by ekantane          #+#    #+#             */
/*   Updated: 2023/01/27 18:43:12 by ikarjala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static inline int	print_usage(void)
{
	const char	msg[] = "usage: " BIN_NAME " <scene_description_file>\n";

	write (1, msg, sizeof(msg) - sizeof(char));
	return (XC_ERROR);
}

static inline int	init_sdl(t_sdl *sdl)
{
	const char		error_msg[] = "Unable to initialize SDL.";
	const t_hookfun	errhook = NULL;

	sdl->ps = ECONTINUE;
	if (SDL_Init (esdl_dev) != 0)
		return (ft_panic (error_msg, errhook));
	sdl->win = SDL_CreateWindow (
			WIN_TITLE, esdl_winpos, esdl_winpos,
			WIN_W, WIN_H, esdl_winflags);
	sdl->surf = SDL_GetWindowSurface (sdl->win);
	if (!sdl->win || !sdl->surf)
		return (ft_panic (error_msg, errhook));
	return (0);
}

/* args
 * parse
 * SDL init
 * events -> render -> raytrace
*/
int	main(int argc, char **argv)
{
	t_sdl		sdl;
	SDL_Event	event;

	if (argc != 2)
		return (print_usage ());
	else if (ft_parse (open (argv[1], O_RDONLY), &sdl.ctx) == -1
		|| init_sdl(&sdl) == -1)
		return (XC_ERROR);
	render (&sdl);
	while (sdl.ps == ECONTINUE)
	{
		while (SDL_PollEvent(&event))
		{
			if ((SDL_QUIT == event.type) || (SDL_KEYDOWN == event.type
					&& SDL_SCANCODE_ESCAPE == event.key.keysym.scancode))
				sdl.ps = EEXIT;
		}
	}
	scene_unload (&sdl.ctx);
	SDL_Quit ();
	return (XC_EXIT);
}
