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
#include <stdio.h>

void	draw_wall(t_world *world, float lenray, int col, int color)
{
	float	len;
	int		i;
	int		y;
	int		max;
	int		(*screen)[WIN_W];

	screen = (int (*)[WIN_W])world->screen;
	len = ((float)WIN_H / lenray);
	y = (WIN_H / 2) - (int)(len * 0.5f);
	max = (WIN_H / 2) + (int)(len * 0.5f);
	if (max > WIN_H)
		max = WIN_H;
	if (y < 0)
		y = 0;
	i = -1;
	while (++i < y)
		screen[i][col] = 0xFF000;
	y--;
	while (++y < max)
		screen[y][col] = color;
	y--;
	while (++y < WIN_H)
		screen[y][col] = 0xFF0;
}

float	dstman(t_vec a, t_vec b)
{
	return (fabsf(a.x - b.x) + fabsf(a.y - b.y));
}

float	distance(t_vec a, t_vec b)
{
	t_vec	total;

	total.x = fabsf(a.x - b.x);
	total.y = fabsf(a.y - b.y);
	return (sqrtf(total.x * total.x + total.y * total.y));
}

int		check(t_ray ray)
{
	if (ray.start.x - ray.dec >= 0 && ray.start.y - ray.dec >= 0 &&
			ray.start.x - ray.dec < 50 && ray.start.y - ray.dec < 50)
		return (1);
	return (0);
}

t_hit		dda2(t_world *world, t_ray rayx, t_ray rayy, t_vec pos)
{
	char	(*map)[50];
	t_vec	dist;
	t_ivec	flag;

	map = (char (*)[50])world->map;
	flag = (t_ivec){1, 1};
	while (flag.x && flag.y)
	{
		dist = (t_vec){dstman(pos, rayx.start), dstman(pos, rayy.start)};
		if (flag.x && dist.x < dist.y && (flag.x = check(rayx)))
		{
			if (map[(int)rayx.start.y][(int)rayx.start.x - rayx.dec] != ' ')
				return ((t_hit){rayx.start, world->colors[rayx.dec]});
			rayx.start.x += rayx.delta.x;
			rayx.start.y += rayx.delta.y;
		}
		if (flag.y && dist.x >= dist.y && (flag.y = check(rayy)))
		{
			if (map[(int)rayy.start.y - rayy.dec][(int)rayy.start.x] != ' ')
				return ((t_hit){rayy.start, world->colors[rayy.dec + 2]});
			rayy.start.x += rayy.delta.x;
			rayy.start.y += rayy.delta.y;
		}
	}
	return ((t_hit){{-1, -1}, 0xff});
}

float	norme(t_vec vec)
{
	return (sqrtf(vec.x * vec.x + vec.y * vec.y));
}

t_vec	ray_vector(t_player *play, int x)
{
	t_vec ray;

	ray.x = play->pos.x + play->dir.x;
	ray.y = play->pos.y + play->dir.y;
	ray.x += play->cam.x * ((x - H_WIN_W) / (float)WIN_W);
	ray.y += play->cam.y * ((x - H_WIN_W) / (float)WIN_W);
	return (ray);
}

void	build_ray(t_vec pos, t_vec ray, t_ray *rayx, t_ray *rayy)
{
	t_vec	diff;
	t_vec	slope;

	diff.x = (ray.x - pos.x);
	diff.y = (ray.y - pos.y);
	slope.y = (diff.x) / (diff.y);
	slope.x = (diff.y) / (diff.x);
	rayx->start.x = floorf(pos.x + (diff.x > 0));
	rayx->start.y = (rayx->start.x - pos.x) * (slope.x) + pos.y;
	rayy->start.y = floorf(pos.y + (diff.y > 0));
	rayy->start.x = (rayy->start.y - pos.y) * (slope.y) + pos.x;
	rayx->delta.x = diff.x / fabsf(diff.x);
	rayx->delta.y = diff.y / fabsf(diff.x);
	rayy->delta.y = diff.y / fabsf(diff.y);
	rayy->delta.x = diff.x / fabsf(diff.y);
	rayx->dec = rayx->delta.x < 0;
	rayy->dec = rayy->delta.y < 0;
}

void	raycast2(t_world *world, t_player *play)
{
	int		col;
	t_vec	ray;
	t_ray	rays[2];
	t_hit	hit;

	col = 0;
	while (col < WIN_W)
	{
		ray = ray_vector(play, col);
		build_ray(play->pos, ray, &rays[0], &rays[1]);
		hit = dda2(world, rays[0], rays[1], play->pos);
		draw_wall(world,
				distance(hit.hit,
					play->pos) * play->ndir / distance(ray, play->pos),
				col, hit.color);
		col++;
	}
}

void		render(t_data *data)
{
	t_world		*world;

	world = &data->world;
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
		data->player.pos.y += data->player.dir.y * 0.1f;
		data->player.pos.x += data->player.dir.x * 0.1f;
	}
	if (data->keys[125])
	{
		data->player.pos.y -= data->player.dir.y * 0.1f;
		data->player.pos.x -= data->player.dir.x * 0.1f;
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
			(current.tv_sec - last.tv_sec) * 1000000 > 500000 )
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
	data.world.colors= (int [4]){0x426d26, 0xee9a49, 0xff82ab, 0xcd6889};
	data.player.pos = (t_vec){25, 2};
	data.player.dir = vec_rot((t_vec){0, 1}, 0.05f);
	data.player.cam = vec_rot((t_vec){1.0f, 0}, 0.05f);
	data.player.ndir = norme(data.player.dir);
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
