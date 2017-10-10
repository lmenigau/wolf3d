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

int		project(double x)
{
	return (x * (1080 / 50) + 10);
}

t_vec		dda(t_world *world, t_vec ray, t_vec delta, t_vec2 dir)
{
	char	(*map)[50];

	map = (char (*)[50])world->map;
	while (ray.x >= 0 && ray.x <= world->size.x
			&& ray.y >= 0 && ray.y <= world->size.y)
	{
		world->debug[project(ray.y)][project(ray.x)] = 0xF0FF33;
		if(map[(int)(ray.y) + dir.y][(int)(ray.x) + dir.x] != ' ')
		{
			world->debug[project(ray.y)][project(ray.x)] = 0xFF0000;
			return (ray);
		}
		ray.x += delta.x;
		ray.y += delta.y;
	}
	return (ray);
}

void	draw_wall(t_world *world, double lenray, int col, int color)
{
	int		len;
	int		y;

	len = ((double)WIN_H / lenray) * (WIN_W/(double)WIN_H);
	y = (WIN_H / 2) - len / 2;
	if (y < 0)
		y = 0;
	while (y < WIN_H && y <= len / 2 + WIN_H / 2)
	{
		world->screen[y][col] = color;
		y++;
	}
}

double	dstman(t_vec a, t_vec b)
{
	t_vec	total;

	total.x = fabs(a.x - b.x);
	total.y = fabs(a.y - b.y);
	return (total.x + total.y);
}

double	distance(t_vec a, t_vec b)
{
	t_vec	total;

	total.x = fabs(a.x - b.x);
	total.y = fabs(a.y - b.y);
	return (sqrtf(total.x * total.x + total.y * total.y));
}

int		boundcheck(t_vec vec)
{
	if (vec.x >= 0 && vec.y >= 0 && vec.x <= 50 && vec.y <= 50)
		return (1);
	return (0);
}

t_vec		dda2(t_world *world, t_ray small, t_ray big,  t_vec pos)
{
	char	(*map)[50];
	t_vec	dist;
	int		maxcount;

	map = (char (*)[50])world->map;
	maxcount = -1;
	while (++maxcount < 50)
	{
		dist = (t_vec){dstman(pos, small.start), dstman(pos, big.start)};
		if (boundcheck(small.start) &&  dist.x <= dist.y)
		{
			if (map[(int)small.start.y][(int)small.start.x] != ' ')
				return (small.start);
			small.start.x += small.delta.x;
			small.start.y += small.delta.y;
		}
		else if (boundcheck(big.start) && dist.x > dist.y)
		{
			if (map[(int)big.start.y][(int)big.start.x] != ' ')
				return (big.start);
			big.start.x += big.delta.x;
			big.start.y += big.delta.y;
		}
	}
	return (t_vec){-1, -1};
}

void	raycast2(t_world *world, t_player *playe)
{
	int		x;
	t_vec	ray;
	t_vec	diff;
	t_vec	slope;
	t_vec	pos;
	t_ray	vert;
	t_ray	horiz;
	t_vec	hit;
	double	magicdist;

	x = 0;
	pos = playe->pos;
	while (x < WIN_W)
	{
		ray.x = playe->pos.x + playe->dir.x;
		ray.y = playe->pos.y + playe->dir.y;
		ray.x += playe->cam.x * ((x - WIN_W / 2.0) / (double)WIN_W);
		ray.y += playe->cam.y * ((x - WIN_W / 2.0) / (double)WIN_W);
		magicdist = sqrt(playe->dir.x * playe->dir.x + playe->dir.y * playe->dir.y) / (distance(ray, pos));
		world->debug[project(ray.y)][project(ray.x)] = 0xff0000;
		diff.x = (ray.x - playe->pos.x);
		diff.y = (ray.y - playe->pos.y);
		slope.y = (diff.x) / (diff.y);
		slope.x = (diff.y) / (diff.x);
		vert.start.x = floor(pos.x + (diff.x > 0));
		vert.start.y = (vert.start.x - pos.x) * (slope.x) + pos.y;
		horiz.start.y = floor(pos.y + (diff.y > 0));
		horiz.start.x = (horiz.start.y - pos.y) * (slope.y) + pos.x;
		vert.delta.x = diff.x / fabs(diff.x);
		vert.delta.y = diff.y / fabs(diff.x);
		horiz.delta.y = diff.y / fabs(diff.y);
		horiz.delta.x = diff.x / fabs(diff.y);
		if (boundcheck(vert.start))
			world->debug[project(vert.start.y)][project(vert.start.x)] = 0xFF0000;
		if (boundcheck(horiz.start))
			world->debug[project(horiz.start.y)][project(horiz.start.x)] = 0x0000FF;
		hit = dda2(world, horiz, vert, pos);
		if (hit.x != -1)
			draw_wall(world, distance(hit, pos) * magicdist, x, 0xFF);
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
	double	magicdist;

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
		ray.x += playe->cam.x * ((x - WIN_W /2.0)/(double)WIN_W);
		ray.y += playe->cam.y * ((x - WIN_W /2.0)/(double)WIN_W);
		magicdist = sqrt(playe->dir.x * playe->dir.x + playe->dir.y * playe->dir.y) / (distance(ray, pos));
		world->debug[project(ray.y)][project(ray.x)] = 0xff0000;
		diff.x = ray.x - playe->pos.x;
		diff.y = ray.y - playe->pos.y;
		slope.x = fabs(diff.x / diff.y);
		slope.y = fabs(diff.y / diff.x);
		delta.x = slope.x * (diff.x / fabs(diff.x));
		delta.y = diff.y / fabs(diff.y);
		if ((delta.x > 0 && delta.y < 0) || (delta.x < 0 && delta.y > 0))
			slope.x = -slope.x;
		if (delta.y < 0)
			dec.y = 0;
		start.y = floor(pos.y + dec.y);
		start.x = (start.y - pos.y) * slope.x  + pos.x;
		hit = (t_vec){-1, -1};
		if (delta.y < 0)
			dir.y = -1;
		if ((start.x > 0 && start.x < world->size.x
					&& start.y > 0 && start.y < world->size.y))
		{
			hit = dda(world, start, delta, dir);
			world->debug[project(start.y)][project(start.x)] = 0xFFF0FF;
		}
		dir = (t_vec2){0, 0};
		delta2.x = diff.x / fabs(diff.x);
		delta2.y = slope.y * (diff.y / fabs(diff.y));
		if ((delta2.x > 0 && delta2.y < 0) || (delta2.x < 0 && delta2.y > 0))
			slope.y = -slope.y;
		if (delta2.x < 0)
			dec.x = 0;
		start2.x = floor(pos.x + dec.x);
		start2.y = (start2.x - pos.x) * slope.y + pos.y;
		hit2 = (t_vec){-1, -1};
		if (delta2.x < 0)
			dir.x = -1;
		if ((start2.x > 0 && start2.x < world->size.x
					&& start2.y > 0 && start2.y < world->size.y))
		{
			hit2 = dda(world, start2, delta2, dir);
			world->debug[project(start2.y)][project(start2.x)] = 0xFF00FF;
		}
		double len1 = 20000;
		double len2 = 20000;
		if (hit.x != -1)
			len1 = distance(hit, pos);
		if (hit2.x != -1)
			len2 = distance(hit2, pos);
		if (len1 <= len2 )
		{
			if (hit.x != -1)
				draw_wall(world, len1 * magicdist, x, 0xFF);
		}
		else
		{
			if (hit2.x != -1)
				draw_wall(world, len2 * magicdist, x, 0xFFFF);
		}
		x++;
	}
}

void		render(t_data *data)
{
	void		*img;
	void		*imgd;
	int			shit;
	t_world		*world;

	world = &data->world;
	img = mlx_new_image(data->mlx, WIN_W, WIN_H);
	imgd = mlx_new_image(data->mlx, WIN_W, WIN_H);
	world->screen = (int (*)[])mlx_get_data_addr(img, &shit, &shit, &shit);
	world->debug = (int (*)[])mlx_get_data_addr(imgd, &shit, &shit, &shit);
	raycast2(&data->world, &data->player);
	mlx_put_image_to_window(data->mlx, data->win, img, 0, 0);
	mlx_put_image_to_window(data->mlx, data->wind, imgd, 0, 0);
	mlx_destroy_image(data->mlx, img);
	mlx_destroy_image(data->mlx, imgd);
}

t_vec	vec_rot(t_vec vec, double angle)
{
	t_vec	res;

	res.x = vec.x * cos(angle) - vec.y * sin(angle);
	res.y = vec.x * sin(angle) + vec.y * cos(angle);
	return (res);
}

void	key_hook(int keycode, t_data *data)
{
	//printf("%d\n", keycode);
	if (keycode == 126)
	{
		data->player.pos.y += data->player.dir.y /3;
		data->player.pos.x += data->player.dir.x /3;
		//	printf("%f, %f\n", data->player.pos.x, data->player.pos.y);
		render(data);
	}
	if (keycode == 125)
	{
		data->player.pos.y -= data->player.dir.y /3;
		data->player.pos.x -= data->player.dir.x /3;
		render(data);
	}
	if (keycode == 124) {
		data->player.dir = vec_rot(data->player.dir, -0.1);
		data->player.cam = vec_rot(data->player.cam, -0.1);
		render(data);
	}
	if (keycode == 123)
	{
		data->player.dir = vec_rot(data->player.dir, 0.1);
		data->player.cam = vec_rot(data->player.cam, 0.1);
		printf("%f\n", distance((t_vec){0, 0}, data->player.cam));
		printf("%f, %f\n", data->player.cam.x, data->player.cam.y);
		render(data);
	}
}

void	mouse_hook(int x, int y)
{
	printf ("%d, %d\n", x, y);
}

int		main(int	argc, char **argv)
{
	t_data		data;

	(void)argc;
	(void)argv;

	data.world.map = init_world();
	data.world.size = (t_vec){50, 50};
	data.player.pos = (t_vec){25, 2.5};
	data.player.dir = ((t_vec){0, 0.5});
	data.player.cam = ((t_vec){0.5, 0});
	data.mlx = mlx_init();
	data.win = mlx_new_window(data.mlx, WIN_W, WIN_H, "wolf3d");
	data.wind = mlx_new_window(data.mlx, WIN_W, WIN_H, "debug");
	mlx_hook(data.win,2, 0, (int (*)())key_hook, &data);
	mlx_hook(data.win,6, 0, (int (*)())mouse_hook, &data);
	render(&data);
	mlx_loop(data.mlx);
}
