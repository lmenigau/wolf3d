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

t_vec		dda(t_world *world, t_vec ray, t_vec delta)
{
	char	(*map)[50];

	map = (char (*)[50])world->map;
	map[15][27] = 'X';
	map[25][30] = 'X';
	while (ray.x >= 0 && ray.x < world->size.x
			&& ray.y >= 0 && ray.y < world->size.y)
	{
		world->debug[project(ray.y)][project(ray.x)] = 0xF0FF33;
		if(map[(int)(ray.y)][(int)(ray.x)] != ' ')
		{
			/* printf("ray: %d %d double:", (int)ray.x, (int)ray.y); */
			/* printf("ray: %f %f\n", ray.x, ray.y); */
			/* printf("delta: %f %f\n", delta.x, delta.y); */
			return (ray);
		}
		ray.x += delta.x;
		ray.y += delta.y;
	}
	//printf("\n\n\ncharhti: %c\n", map[(int)(ray.y)][(int)(ray.x)]);
	return (ray);
}

void	draw_wall(t_world *world, t_player *player, t_vec ray, t_vec hit, int col, int color)
{
	int 	len;
	double	lenray;
	t_vec	total;
	int		y;

	(void)player;
	total.x = fabs(hit.x - ray.x);
	total.y = fabs(hit.y - ray.y);
	lenray = sqrtf(total.x * total.x + total.y * total.y);
	//printf("%f, %f\n", hit.x, hit.y);
	len =  ((double)WIN_H / lenray * WIN_W / WIN_H);
	//printf("%f\n", lenray);
	y = (WIN_H / 2) - len / 2;
	while (y >= 0 && y < WIN_H && y <= len / 2 + WIN_H / 2)
	{
		world->screen[y][col] = color;
		y++;
	}
}

double	distance(t_vec a, t_vec b)
{
	t_vec total;
	total.x = fabs(a.x - b.x);
	total.y = fabs(a.y - b.y);
	return (sqrtf(total.x * total.x + total.y * total.y));
}

void	raycast(t_world *world, t_player *playe)
{
	int x;
	int color;
	t_vec	ray;
	t_vec	diff;
	t_vec	slope;
	t_vec	hit;
	t_vec	delta;
	t_vec	delta2;
	t_vec	hit2;
	t_vec	 start;
	t_vec	 start2;

	t_vec	pos;
	pos = playe->pos;
	x = 0;
	while (x < WIN_W)
	{
	int vdec = 1;
	int hdec = 1;
		ray.x = playe->pos.x + playe->dir.x ;
		ray.y = playe->pos.y + playe->dir.y ;
		ray.x += playe->cam.x * ((x - WIN_W /2.0)/(double)WIN_W);
		ray.y += playe->cam.y * ((x - WIN_W /2.0)/(double)WIN_W);
		world->debug[project(ray.y)][project(ray.x)] = 0xff0000;
		diff.x = ray.x - playe->pos.x;
		diff.y = ray.y - playe->pos.y;
		slope.x = fabs(diff.x / diff.y);
		slope.y = fabs(diff.y / diff.x);
		delta.x = slope.x * (diff.x / fabs(diff.x));
		delta.y = diff.y / fabs(diff.y);
		if ((delta.x < 0 && delta.y > 0)|| (delta.x > 0 && delta.y < 0))
			slope.x = -slope.x;
		if (delta.y < 0)
			hdec = -1;
		start.y = round(pos.y + hdec);
		start.x = (start.y - pos.y) * slope.x  + pos.x;
		hit.x = -1;
		if ((start.x >= 0 && start.x < world->size.x
					&& start.y >= 0 && start.y < world->size.y))
		{
			world->debug[project(start.y)][project(start.x)] = 0xFFFFFF;
			hit = dda(world, start, delta);
		}
		delta2.x = diff.x / fabs(diff.x);
		delta2.y = slope.y * (diff.y / fabs(diff.y));
		if ((delta2.x < 0 && delta2.y > 0) || (delta2.x > 0 && delta2.y < 0))
			slope.y = -slope.y;
		if (delta2.x < 0)
			vdec = -1;
		start2.x = round(pos.x + vdec);
		start2.y = (start2.x - pos.x) * slope.y + pos.y;
		hit2.x = -1;
		if ((start2.x >= 0 && start2.x < world->size.x
					&& start2.y >= 0 && start2.y < world->size.y))
		{
			hit2 = dda(world, start2, delta2);
			world->debug[project(start2.y)][project(start2.x)] = 0xFF00FF;
		}
		if (fabs(delta.x) > fabs(delta2.y))
			color = 0xff;
		else
			color = 0xffff;
		int len1;
		int len2;
		len1 = distance(hit, pos);
		len2 = distance(hit2, pos);
		if (len1 < len2 )
		{
			if (hit.x != -1) {
				draw_wall(world, playe, pos, hit, x, color);
				/* plotline_vec(world->debug, (t_vec2){project(hit.x), project(hit.y) }, */
				/* 		(t_vec2){project(ray.x), project(ray.y)}, color); */
			}
		}
		else
		{
			if (hit2.x != -1) {
				draw_wall(world, playe, pos, hit2, x, color);
				/* plotline_vec(world->debug, (t_vec2){project(hit2.x), project(hit2.y) }, */
				/* 		(t_vec2){project(ray.x), project(ray.y)}, color); */
			}
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
	raycast(&data->world, &data->player);
	//	printf("End\n");
	mlx_put_image_to_window(data->mlx, data->win, img, 0, 0);
	mlx_put_image_to_window(data->mlx, data->wind, imgd, 0, 0);
	mlx_destroy_image(data->mlx, img);
	mlx_destroy_image(data->mlx, imgd);
}

t_vec		vec_rot(t_vec vec, double angle)
{
	t_vec	res;
	res.x = vec.x * cos(angle) - vec.y * sin(angle);
	res.y = vec.x * sin(angle) + vec.y * cos(angle);
	return (res);
}

void	key_hook(int keycode, t_data *data)
{
	printf("%d\n", keycode);
	if (keycode == 126)
	{
		data->player.pos.y += data->player.dir.y /3;
		data->player.pos.x += data->player.dir.x /3;
		printf("%f, %f\n", data->player.pos.x, data->player.pos.y);
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
		printf("%f\n", distance((t_vec){0,0}, data->player.cam));
		printf("%f, %f\n", data->player.cam.x, data->player.cam.y);
		render(data);
	}
}

int			main(int	argc, char **argv)
{
	t_data		data;

	(void)argc;
	(void)argv;

	data.world.map = init_world();
	data.world.size = (t_vec){50, 50};
	data.player.pos = (t_vec){25.1, 2.2};
	data.player.dir = ((t_vec){0, 0.7});
	data.player.cam = ((t_vec){0.7, 0});
	data.mlx = mlx_init();
	data.win = mlx_new_window(data.mlx, WIN_W, WIN_H, "wolf3d");
	data.wind = mlx_new_window(data.mlx, WIN_W, WIN_H, "debug");
	mlx_hook(data.win,2, 0, (int (*)())key_hook, &data);
	render(&data);
	mlx_loop(data.mlx);
}
