/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmenigau <lmenigau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/09 03:50:26 by lmenigau          #+#    #+#             */
/*   Updated: 2017/05/24 20:33:12 by lmenigau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"
#include "fdf.h"
#include <stdio.h> //

int		project(float x)
{
	return ((int)(x * (1080 / 50) + 10));
}

t_vec		dda(t_world *world, t_vec ray, t_vec delta, t_vec2 dir)
{
	char	(*map)[50];

	map = (char (*)[50])world->map;
	while (ray.x >= 0 && ray.x <= world->size.x
			&& ray.y >= 0 && ray.y <= world->size.y)
	{
		//world->debug[project(ray.y)][project(ray.x)] = 0xF0FF33;
		if(map[(int)(ray.y) + dir.y][(int)(ray.x) + dir.x] != ' ')
		{
			//world->debug[project(ray.y)][project(ray.x)] = 0xFF0000;
			return (ray);
		}
		ray.x += delta.x;
		ray.y += delta.y;
	}
	return (ray);
}

void	draw_wall(t_world *world, float lenray, int col, int color)
{
	float	len;
	int		y;
	int		max;
	int		(*screen)[WIN_W];

	screen = (int (*)[WIN_W])world->screen;
	len = (WIN_H / lenray) * (WIN_W/(float)WIN_H);
	y = (WIN_H / 2) - (int)(len / 2.0f);
	max = (WIN_H / 2) + (int)(len /2.0f); 
	if (max > WIN_H)
		max = WIN_H;
	if (y < 0)
		y = 0;
	while (y <= max)
	{
		screen[y][col] = color;
		y++;
	}
}

float	dstman(t_vec a, t_vec b)
{
	t_vec	total;

	total.x = fabsf(a.x - b.x);
	total.y = fabsf(a.y - b.y);
	return (total.x + total.y);
}

float	distance(t_vec a, t_vec b)
{
	t_vec	total;

	total.x = fabsf(a.x - b.x);
	total.y = fabsf(a.y - b.y);
	return (sqrtf(total.x * total.x + total.y * total.y));
}

int		boundcheck(t_vec vec, t_ivec dec)
{
	if (vec.x + dec.x >= 0 && vec.y + dec.y >= 0 && vec.x + dec.x <= 50 && vec.y + dec.y <= 50)
		return (1);
	return (0);
}

t_vec		dda2(t_world *world, t_ray rayx, t_ray rayy, t_vec pos)
{
	char	(*map)[50];
	t_vec	dist;
	int		maxcount;

	map = (char (*)[50])world->map;
	maxcount = -1;
	while (++maxcount < 100)
	{
		dist = (t_vec){dstman(pos, rayx.start), dstman(pos, rayy.start)};
		if (boundcheck(rayx.start, (t_ivec){rayx.dec, 0}) && dist.x <= dist.y)
		{
			if (map[(int)rayx.start.y][(int)rayx.start.x - rayx.dec] != ' ')
				return (rayx.start);
			rayx.start.x += rayx.delta.x;
			rayx.start.y += rayx.delta.y;
		}
		else if (boundcheck(rayy.start, (t_ivec){0, rayy.dec}) && dist.x > dist.y)
		{
			if (map[(int)rayy.start.y - rayy.dec][(int)rayy.start.x] != ' ')
				return (rayy.start);
			rayy.start.x += rayy.delta.x;
			rayy.start.y += rayy.delta.y;
		}
	}
	return (pos);
}

void	raycast2(t_world *world, t_player *playe)
{
	int		x;
	t_vec	ray;
	t_vec	diff;
	t_vec	slope;
	t_vec	pos;
	t_ray	horiz;
	t_ray	vert;
	t_vec	hit;
	float	magicdist;
	//static int	tab[2][2] = {{0xFF, 0xFF0}, {0xFFFF, 0xFF00}};

	x = 0;
	pos = playe->pos;
	while (x < WIN_W)
	{
		ray.x = playe->pos.x + playe->dir.x;
		ray.y = playe->pos.y + playe->dir.y;
		ray.x += playe->cam.x * ((x - WIN_W / 2.0f) / (float)WIN_W);
		ray.y += playe->cam.y * ((x - WIN_W / 2.0f) / (float)WIN_W);
		magicdist = sqrtf(playe->dir.x * playe->dir.x + playe->dir.y * playe->dir.y) / (distance(ray, pos));
		diff.x = (ray.x - playe->pos.x);
		diff.y = (ray.y - playe->pos.y);
		slope.y = (diff.x) / (diff.y);
		slope.x = (diff.y) / (diff.x);
		vert.start.x = floorf(pos.x + (diff.x > 0));
		vert.start.y = (vert.start.x - pos.x) * (slope.x) + pos.y;
		horiz.start.y = floorf(pos.y + (diff.y > 0));
		horiz.start.x = (horiz.start.y - pos.y) * (slope.y) + pos.x;
		vert.delta.x = diff.x / fabsf(diff.x);
		vert.delta.y = diff.y / fabsf(diff.x);
		horiz.delta.y = diff.y / fabsf(diff.y);
		horiz.delta.x = diff.x / fabsf(diff.y);
		vert.dec = vert.delta.x < 0;
		horiz.dec = horiz.delta.y < 0;
		hit = dda2(world, vert, horiz, pos);
		//printf ("%f, %f\n", (double)vert.start.y, (double)horiz.start.x);
		draw_wall(world, distance(hit, pos) * magicdist, x, 98493);
		x++;
	}
}

void	raycast(t_world *world, t_player *playe)
{
	int		x;
	t_vec	ray;
	t_vec	diff;
	t_vec	slope;
	t_vec	hit;
	t_vec	delta;
	t_vec	delta2;
	t_vec	hit2;
	t_vec	start;
	t_vec	start2;
	t_vec	pos;
	float	magicdist;

	pos = playe->pos;
	x = 0;
	while (x < WIN_W)
	{
		t_vec2 dec;
		t_vec2 dir;
		dec = (t_vec2){1, 1};
		dir = (t_vec2){0, 0};
		ray.x = playe->pos.x + playe->dir.x;
		ray.y = playe->pos.y + playe->dir.y;
		ray.x += playe->cam.x * ((x - WIN_W /2.0f)/(float)WIN_W);
		ray.y += playe->cam.y * ((x - WIN_W /2.0f)/(float)WIN_W);
		magicdist = sqrtf(playe->dir.x * playe->dir.x + playe->dir.y * playe->dir.y) / (distance(ray, pos));
		//world->debug[project(ray.y)][project(ray.x)] = 0xff0000;
		diff.x = ray.x - playe->pos.x;
		diff.y = ray.y - playe->pos.y;
		slope.x = fabsf(diff.x / diff.y);
		slope.y = fabsf(diff.y / diff.x);
		delta.x = slope.x * (diff.x / fabsf(diff.x));
		delta.y = diff.y / fabsf(diff.y);
		if ((delta.x > 0 && delta.y < 0) || (delta.x < 0 && delta.y > 0))
			slope.x = -slope.x;
		if (delta.y < 0)
			dec.y = 0;
		start.y = floorf(pos.y + dec.y);
		start.x = (start.y - pos.y) * slope.x  + pos.x;
		hit = (t_vec){-1, -1};
		if (delta.y < 0)
			dir.y = -1;
		if ((start.x > 0 && start.x < world->size.x
					&& start.y > 0 && start.y < world->size.y))
		{
			hit = dda(world, start, delta, dir);
			//world->debug[project(start.y)][project(start.x)] = 0xFFF0FF;
		}
		dir = (t_vec2){0, 0};
		delta2.x = diff.x / fabsf(diff.x);
		delta2.y = slope.y * (diff.y / fabsf(diff.y));
		if ((delta2.x > 0 && delta2.y < 0) || (delta2.x < 0 && delta2.y > 0))
			slope.y = -slope.y;
		if (delta2.x < 0)
			dec.x = 0;
		start2.x = floorf(pos.x + dec.x);
		start2.y = (start2.x - pos.x) * slope.y + pos.y;
		hit2 = (t_vec){-1, -1};
		if (delta2.x < 0)
			dir.x = -1;
		if ((start2.x > 0 && start2.x < world->size.x
					&& start2.y > 0 && start2.y < world->size.y))
		{
			hit2 = dda(world, start2, delta2, dir);
			//world->debug[project(start2.y)][project(start2.x)] = 0xFF00FF;
		}
		float len1 = 20000;
		float len2 = 20000;
		if (hit.x > -1)
			len1 = distance(hit, pos);
		if (hit2.x > -1)
			len2 = distance(hit2, pos);
		if (len1 <= len2 )
		{
			if (hit.x > -1)
				draw_wall(world, len1 * magicdist, x, 0xFF);
		}
		else
		{
			if (hit2.x > -1)
				draw_wall(world, len2 * magicdist, x, 0xFFFF);
		}
		x++;
	}
}
#include <strings.h>
void		render(t_data *data)
{
	t_world		*world;

	world = &data->world;
	bzero(world->screen, WIN_W * WIN_H * 4);
	raycast2(&data->world, &data->player);
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
}

t_vec	vec_rot(t_vec vec, float angle)
{
	t_vec	res;

	res.x = vec.x * cosf(angle) - vec.y * sinf(angle);
	res.y = vec.x * sinf(angle) + vec.y * cosf(angle);
	return (res);
}

void	key_hook(t_data *data)
{
	if (data->keys[126])
	{
		data->player.pos.y += data->player.dir.y /2;
		data->player.pos.x += data->player.dir.x /2;
	}
	if (data->keys[125])
	{
		data->player.pos.y -= data->player.dir.y /2;
		data->player.pos.x -= data->player.dir.x /2;
	}
	if (data->keys[124])
	{
		data->player.dir = vec_rot(data->player.dir, -0.05f);
		data->player.cam = vec_rot(data->player.cam, -0.05f);
	}
	if (data->keys[123])
	{
		data->player.dir = vec_rot(data->player.dir, 0.05f);
		data->player.cam = vec_rot(data->player.cam, 0.05f);
	}
}

void	key_press(int keycode, int *keys)
{
	keys[keycode] = 1;	
}

void	key_release(int keycode, int *keys)
{
	keys[keycode] = 0;
}

void 	fps_counter(t_data *data)
{
	static struct timeval	last;
	static long				frames;
	struct timeval 			current;
	static char				str[30];

	if (last.tv_sec == 0)
		gettimeofday(&last, NULL);
	frames++;
	gettimeofday(&current, NULL);
	if ((current.tv_usec - last.tv_usec) +
			(current.tv_sec - last.tv_sec) * 1000000 > 250000 )
	{

		sprintf(str, "%ld", frames * 1000000 / ((current.tv_usec - last.tv_usec) 
					+ (current.tv_sec - last.tv_sec) * 1000000));
		last = current;
		frames = 0;
	}
	mlx_string_put(data->mlx, data->win, 10, 10, 0xFFFFFF, str);
}

void 	loop(t_data *data)
{
	key_hook(data);
	render(data);
	fps_counter(data);
}

void	mouse_hook(int x, int y)
{
	(void)x;
	(void)y;
	//printf ("%d, %d\n", x, y);
}

int		main(int	argc, char **argv)
{
	t_data			data;
	static int		keys[MAX_KEY];
	int				bs;

	(void)argc;
	(void)argv;

	data.keys = keys;
	data.world.map = init_world();
	data.world.size = (t_vec){50, 50};
	data.player.pos = (t_vec){25, 2};
	data.player.dir = ((t_vec){0, 0.5});
	data.player.cam = ((t_vec){0.5, 0});
	data.mlx = mlx_init();
	data.win = mlx_new_window(data.mlx, WIN_W, WIN_H, "wolf3d");
	data.img = mlx_new_image(data.mlx, WIN_W, WIN_H);
	data.world.screen = (int (*)[])mlx_get_data_addr(data.img, &bs, &bs, &bs);
	//	data.wind = mlx_new_window(data.mlx, WIN_W, WIN_H, "debug");
	mlx_hook(data.win,2, 0, (int (*)())key_press, keys);
	mlx_hook(data.win,3, 0, (int (*)())key_release, keys);
	mlx_hook(data.win,6, 0, (int (*)())mouse_hook, &data);
	mlx_loop_hook(data.mlx, (int (*)())loop, &data);
	mlx_loop(data.mlx);
}
