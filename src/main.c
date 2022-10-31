/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekantane <ekantane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 14:19:38 by ekantane          #+#    #+#             */
/*   Updated: 2022/10/31 15:59:16 by ekantane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>

/* *** THE VECTOR FUNCTIONS *** */

/* Subtract two vectors and return the resulting vector */
vector vectorSub(vector *v1, vector *v2){
	vector result = {v1->x - v2->x, v1->y - v2->y, v1->z - v2->z };
	return result;
}

/* Multiply two vectors and return the resulting scalar (dot product) */
float vectorDot(vector *v1, vector *v2){
	return v1->x * v2->x + v1->y * v2->y + v1->z * v2->z;
}

/* *** MAIN *** */

/* Check if the ray and sphere intersect */
int intersectRaySphere(ray *r, sphere *s){
	
	/* A = d.d, the vector dot product of the direction */
	float A = vectorDot(&r->dir, &r->dir); 
	
	/* We need a vector representing the distance between the start of 
	 * the ray and the position of the circle.
	 * This is the term (p0 - c) 
	 */
	vector dist = vectorSub(&r->start, &s->pos);
	
	/* 2d.(p0 - c) */  
	float B = 2 * vectorDot(&r->dir, &dist);
	
	/* (p0 - c).(p0 - c) - r^2 */
	float C = vectorDot(&dist, &dist) - (s->radius * s->radius);
	
	/* Solving the discriminant */
	float discr = B * B - 4 * A * C;
	
	/* If the discriminant is negative, there are no real roots.
	 * Return false in that case as the ray misses the sphere.
	 * Return true in all other cases (can be one or two intersections)
	 */
	if(discr < 0)
		return (0);
	else
		return (1);
}

void loop(t_rtv	*rtv)
{

	int x;
	int y;
	int	quit;
	sphere s;
	ray r;

	quit = 0;
	y = 0;
	x = 0;

	/* Position the sphere */
	s.pos.x = 120;
	s.pos.y = 120;
	s.pos.z = 20;

	/* Sphere radius */
	s.radius = 100;

	/* Direction of the ray */
	r.dir.x = 0;
	r.dir.y = 0;
	r.dir.z = 1;

	/* Start position of the ray, z coordinate */
	r.start.z = 0;

	/* Iterate over every pixel of our screen */
	while(y < HEIGHT)
	{
		x = 0;
		/* Set the y-coordinate of the start position of the ray */
		r.start.y = y; 
		while(x < WIDTH)
		{
			/* Set the x-coordinate of the start position of the ray */
			r.start.x = x;
			
			/* Check if the ray intersects with the shpere */
			if(intersectRaySphere(&r, &s) == 1)
			{
				SDL_RenderDrawLine(rtv->ren, r.start.x + r.start.y, r.start.y, r.dir.x, r.dir.y);
			}
			else
			{
				SDL_SetRenderDrawColor(rtv->ren, 0, 0, 0, 0xFF);
				SDL_RenderDrawPoint(rtv->ren, x, y);
			}
			x++;
		}
		y++;
	}
	/* Got everything on rendering surface, now Update the drawing image on window screen */
	SDL_UpdateWindowSurface(rtv->win);
	while (quit == 0)
	{
		while (SDL_PollEvent(&rtv->event))
		{
			if (rtv->event.type == SDL_QUIT)
				quit = 1;
			if (rtv->event.type == SDL_KEYDOWN)
				if (rtv->event.key.keysym.sym == SDLK_ESCAPE)
					quit = 1;
		}
	}
	SDL_Quit();
}

int init_sdl(t_rtv	*rtv)
{
	/* Enable standard application logging */
	SDL_LogSetPriority(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO);

	/* Initialize SDL */
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL_Init fail : %s\n", SDL_GetError());
		return (1);
	}
	/* Create window and renderer for given surface */
	rtv->win = SDL_CreateWindow("RTv1: Sphere", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, 0);
	if (!rtv->win) {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Window creation fail : %s\n",SDL_GetError());
		return (1);
	}
	rtv->sur = SDL_GetWindowSurface(rtv->win);
	rtv->ren = SDL_CreateSoftwareRenderer(rtv->sur);
	if (!rtv->ren) {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Render creation for surface fail : %s\n",SDL_GetError());
		return (1);
	}
	/* Clear the rendering surface with the specified color */
	SDL_SetRenderDrawColor(rtv->ren, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderClear(rtv->ren);
	/* Draw the Image on rendering surface */
	init_sdl(rtv);
	return 0;
}

int main(int argc, char **argv)
{
	t_rtv	rtv;

	if (argc != 1 && argv != NULL)
	{
		return (1);
	}
	init_sdl(&rtv);
	return 0;
}
