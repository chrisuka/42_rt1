/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekantane <ekantane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 14:19:38 by ekantane          #+#    #+#             */
/*   Updated: 2022/11/02 16:53:41 by ekantane         ###   ########.fr       */
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

/* Calculate Vector x Scalar and return resulting Vector*/ 
vector vectorScale(float c, vector *v)
{
	vector result = {v->x * c, v->y * c, v->z * c };
	return result;
}

/* Add two vectors and return the resulting vector */
vector vectorAdd(vector *v1, vector *v2)
{
	vector result = {v1->x + v2->x, v1->y + v2->y, v1->z + v2->z };
	return result;
}





/* *** MAIN *** */

/* Check if the ray and sphere intersect */
int intersectRaySphere(ray *r, sphere *s, float *t)
{
	
	int retval = 0;
	
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
	 * t represents the distance between the start of the ray and
	 * the point on the sphere where it intersects.
	 */
	if(discr < 0)
		retval = 0;
	else{
		float sqrtdiscr = sqrtf(discr);
		float t0 = (-B + sqrtdiscr)/(2);
		float t1 = (-B - sqrtdiscr)/(2);
		
		/* We want the closest one */
		if(t0 > t1)
			t0 = t1;

		/* Verify t1 larger than 0 and less than the original t */
		if((t0 > 0.001f) && (t0 < *t)){
			*t = t0;
			retval = 1;
		}else
			retval = 0;
	}
return retval;
}

int min(int a, int b)
{
	if (a < b)
		return (a);
	if (a > b)
		return (b);
	return (0);
}

void loop(char *arg, t_rtv	*rtv)
{
	int x;
	int y;
	int	quit;
	ray r;
	unsigned int i;
	unsigned int j;

	sphere spheres;
	light lights;
	camera cam;

	y = 0;
	x = 0;
	char	*line;
	int		fd;
	int		ix;
	char	**spl_res;

	ix = 0;
	fd = 0;
	line = NULL;
	quit = 0;

	
	if ((fd = open(arg, O_RDONLY)) < 0)
		exit(1);
	while ((ix = get_next_line(fd, &line)) > 0)
	{
		spl_res = ft_strsplit(line, ' ');
	if (ft_strequ(spl_res[0], "spheres.pos.x"))
		spheres.pos.x = (double)(atoi(spl_res[1]));
	else if (ft_strequ(spl_res[0], "spheres.pos.y"))
		spheres.pos.y = (double)(atoi(spl_res[1]));
	else if (ft_strequ(spl_res[0], "spheres.pos.z"))
		spheres.pos.z = (double)(atoi(spl_res[1]));
	else if (ft_strequ(spl_res[0], "spheres.radius"))
		spheres.radius = (double)(atoi(spl_res[1]));
	else if (ft_strequ(spl_res[0], "lights.pos.x"))
		lights.pos.x = (double)(atoi(spl_res[1]));
	else if (ft_strequ(spl_res[0], "lights.pos.y"))
		lights.pos.y = (double)(atoi(spl_res[1]));
	else if (ft_strequ(spl_res[0], "lights.pos.z"))
		lights.pos.z = (double)(atoi(spl_res[1]));
	else if (ft_strequ(spl_res[0], "lights.intensity.red"))
		lights.intensity.red = (double)(atoi(spl_res[1]));
	else if (ft_strequ(spl_res[0], "cam.pos.x"))
		cam.pos.x = (double)(atoi(spl_res[1]));
	else if (ft_strequ(spl_res[0], "cam.pos.y"))
		cam.pos.y = (double)(atoi(spl_res[1]));
	else if (ft_strequ(spl_res[0], "cam.pos.z"))
		cam.pos.z = (double)(atoi(spl_res[1]));
		ft_strdel(&line);
	}
	ft_strdel(&line);

	while(y < HEIGHT)
	{
		x = 0;
		while(x < WIDTH)
		{

			float red = 0;
			float green = 0;
			float blue = 0;
			
			int level = 0;
			float coef = 1.0;
			
			r.start.x = x + cam.pos.x;
			r.start.y = y + cam.pos.y;
			r.start.z = -2000 + cam.pos.z;
			
			r.dir.x = 0;
			r.dir.y = 0;
			r.dir.z = 1;


			while((coef > 0.0f) && (level < 15))
			{
				/* Find closest intersection */
				float t = 20000.0f;
				int currentSphere = -1;
				
				i = 0;

				while (i < 3)
				{
					if(intersectRaySphere(&r, &spheres, &t) == 1)
						currentSphere = i;
					i++;

				}
				if(currentSphere == -1) break;

				vector scaled = vectorScale(t, &r.dir);
				vector newStart = vectorAdd(&r.start, &scaled);
				
				/* Find the normal for this new vector at the point of intersection */
				vector n = vectorSub(&newStart, &spheres.pos);
				float temp = vectorDot(&n, &n);
				if(temp == 0) break;
				
				temp = 1.0f / sqrtf(temp);
				n = vectorScale(temp, &n);

				
				/* Find the value of the light at this point */
				j = 0;
				while (j < 3)
				{
					light currentLight = lights;
						j++;					
					vector dist = vectorSub(&currentLight.pos, &newStart);
					if(vectorDot(&n, &dist) <= 0.0f) continue;
					float t = sqrtf(vectorDot(&dist,&dist));
					if(t <= 0.0f) continue;				
					ray lightRay;
					lightRay.start = newStart;
					lightRay.dir = vectorScale((1/t), &dist);
					
					/* Lambert diffusion */
					float lambert = vectorDot(&lightRay.dir, &n) * coef; 
					red += lambert * currentLight.intensity.red;
					green += lambert * currentLight.intensity.green;
					blue += lambert * currentLight.intensity.blue;

				}

				/* The reflected ray start and direction */
				r.start = newStart;
				float reflect = 2.0f * vectorDot(&r.dir, &n);
				vector tmp = vectorScale(reflect, &n);
				r.dir = vectorSub(&r.dir, &tmp);

				level++;

			}
		SDL_SetRenderDrawColor(rtv->ren, min(red*255.0f, 255.0f), min(green*255.0f, 255.0f), min(blue*255.0f, 255.0f), 255);
		SDL_RenderDrawPoint(rtv->ren, x, y);
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

int init_sdl(char *arg, t_rtv	*rtv)
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
	loop(arg, rtv);
	return 0;
}

int main(int argc, char **argv)
{
	t_rtv	rtv;

	if (argc != 2 && argv != NULL)
	{
		return (1);
	}
	init_sdl(argv[1], &rtv);
	return 0;
}
