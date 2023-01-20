/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekantane <ekantane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 14:19:38 by ekantane          #+#    #+#             */
/*   Updated: 2023/01/19 16:09:55 by ikarjala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static inline int	print_usage(void)
{
	const char	msg[] = "usage: " BIN_NAME " <scene_description_file>\n";
	
	write (1, msg, sizeof(msg) - sizeof(char));
	return (XC_ERROR);
}

/*/ UNIT TESTS =============================================================/*/
#define DEBUG 0
#if DEBUG
#include <stdio.h>
static inline void	unit_tests(t_sdl *sdl)
{
	sdl = NULL;
	t_vec d = {1,1,0};
	t_vec n = {0,-1,0};
	t_vec r = vec_reflect (d, n);
	if (r.x == 1 &&
		r.y == -1 &&
		r.z == 0)
		ft_putendl ("success");
}
#endif
/*/ ========================================================================/*/

static inline int	init_sdl(t_sdl *sdl)
{
	const char	error_msg[] = "Unable to initialize SDL.";
	const void	(*errhook) = NULL;

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
int		main(int argc, char **argv)
{
	t_sdl		sdl;
	SDL_Event	event;

	if (argc != 2)
		return (print_usage ());
	else if (ft_parse (open (argv[1], O_RDONLY), &sdl.ctx) == -1
		|| init_sdl(&sdl) == -1)
		return (XC_ERROR);
#if DEBUG
	unit_tests(&sdl); // DEBUG
	return (0);
#endif
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
	// free everything here, then exit with main return
	scene_unload (&sdl.ctx);
	SDL_Quit ();
	return (XC_EXIT);
}
