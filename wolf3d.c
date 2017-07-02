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

t_vec		dda(t_world *world, t_vec ray, t_vec delta)
{
	char	(*map)[(int)world->size.x];

	map = (char (*)[])world->map;
	map[15][27] = 'X';
	map[25][30] = 'X';
	while (ray.x >= 0 && ray.x < world->size.x - 1
			&& ray.y >= 0 && ray.y < world->size.y  -1)
	{
		if(map[(int)(ray.y)][(int)(ray.x)] != ' ')
		{
			printf("ray: %d %d double:", (int)ray.x, (int)ray.y);
			printf("ray: %f %f\n", ray.x, ray.y);
			printf("delta: %f %f\n", delta.x, delta.y);
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
	total.x =  fabs(hit.x - ray.x);
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
	t_vec	hit2;

	t_vec	pos;
	x = 0;
	pos = playe->pos;
	while (x < WIN_W)
	{
		 if (x == 960)
			 x=961;
		ray.x = playe->pos.x + playe->dir.x ;
		ray.y = playe->pos.y + playe->dir.y ;
		ray.x += playe->cam.x * ((x - WIN_W /2)/(double)WIN_W);
		ray.y += playe->cam.y * ((x - WIN_W /2)/(double)WIN_W);
		diff.x = ray.x - playe->pos.x;
		diff.y = ray.y - playe->pos.y;
		slope.x = fabs(diff.x / diff.y);
		slope.y = fabs(diff.y / diff.x);
		delta.x = slope.x * (diff.x / fabs(diff.x));
		delta.y = diff.y / fabs(diff.y);
		t_vec start;
		start.x = 0;
		hit = dda(world, ray, delta);
		delta.x = diff.x / fabs(diff.x);
		delta.y = slope.y * (diff.y / fabs(diff.y));
		hit2 = dda(world, ray, delta);
		if (slope.x <= slope.y)
			color = 0xff;
		else
			color = 0xffff;
		int len1;
		int len2;
		len1 = distance(hit, ray);
		len2 = distance(hit2, ray);
		if (len1 < len2)
		{
			draw_wall(world, playe, ray, hit, x, color);
			plotline_vec(world->debug, (t_vec2){hit.x * (1080/60), hit.y * (1080/60)},
					(t_vec2){ray.x * (1080/60), ray.y * (1080 /60) }, color);
		}
		else
		{
			draw_wall(world, playe, ray, hit2, x, color);
			plotline_vec(world->debug, (t_vec2){hit2.x * (1080/60), hit2.y * (1080/60)},
					(t_vec2){ray.x * (1080/60), ray.y * (1080 /60) }, color);
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
	data.player.dir = ((t_vec){0, 0.5});
	data.player.cam = ((t_vec){0.5, 0});
	data.mlx = mlx_init();
	data.win = mlx_new_window(data.mlx, WIN_W, WIN_H, "wolf3d");
	data.wind = mlx_new_window(data.mlx, WIN_W, WIN_H, "debug");
	mlx_hook(data.win,2, 0, (int (*)())key_hook, &data);
	render(&data);
	mlx_loop(data.mlx);
}
