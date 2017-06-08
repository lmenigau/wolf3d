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

#include <stdio.h> //

t_vec		dda(t_world *world, t_vec ray, t_vec delta)
{
	t_ivec off;
	char	(*map)[(int)world->size.x];

	map = (char (*)[])world->map;
	map[15][27] = 'X';
	map[15][26] = 'X';
	off = (t_ivec){0, 0};
	if (delta.y < 0)
		off.y = 1;
	if (delta.x < 0)
		off.x = 1;
	while (ray.x >= 0 && ray.x < world->size.x - 1
			&& ray.y >= 0 && ray.y < world->size.y  -1)
	{
		if(map[(int)(ray.y) + off.y][(int)(ray.x) + off.x] != ' ')
		{
//			printf("charhti: %hhd\n", map[lroundf(ray.y)][lroundf(ray.x)]);
//			printf("ray: %ld %ld\n", (lroundf)(ray.x), lroundf(ray.y));
//			printf("ray: %f %f\n", ray.x, ray.y);
			printf("ray: %d %d float:", (int)ray.x, (int)ray.y);
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
	float	lenray;
	t_vec	total;
	int		y;

	(void)ray;
	total.x =  fabsf(hit.x - player->pos.x);
	total.y = fabsf(hit.y - player->pos.y);
	lenray = sqrtf(total.x * total.x + total.y * total.y);
////	printf("%f, %f\n", ray.x, ray.y);
	len =  ((float)WIN_H / lenray * WIN_W / WIN_H);
	//printf("%f\n", lenray);
	y = (WIN_H / 2) - len / 2;
	while (y >= 0 && y < WIN_H && y <= len / 2 + WIN_H / 2)
	{
		world->screen[y][col] = color;
		y++;
	}
}

float	distance(t_vec a, t_vec b)
{
		t_vec total;
		total.x =  fabsf(a.x - b.x);
		total.y = fabsf(a.y - b.y);
		return (sqrtf(total.x * total.x + total.y * total.y));
}
void	raycast(t_world *world, t_player *playe)
{
	int		x;
	int color;
	t_vec	ray;
	t_vec	delta;
	t_vec	deltay;
	t_vec	hit;
	t_vec	hit2;
	t_vec save;

	x = 0;
	while (x < WIN_W)
	{
//		//printf("%f\n", ((x - WIN_W /2)/(float)WIN_W));
		ray.x = playe->pos.x + playe->dir.x ;
		ray.y = playe->pos.y + playe->dir.y ;
		ray.x += playe->cam.x * ((x - WIN_W /2)/(float)WIN_W);
		ray.y += playe->cam.y * ((x - WIN_W /2)/(float)WIN_W);
		delta.x = ray.x - playe->pos.x;
		delta.y = ray.y - playe->pos.y;
		deltay.x = delta.y;
		deltay.y = delta.x;
		save = ray;
		if (fabsf(deltay.y) >= fabsf(deltay.x))
		{
			deltay.x /= fabsf(deltay.x);
			deltay.y /= fabsf(deltay.x);
			save.x = (floorf)(ray.x);
			save.y += (floorf)(ray.y) - ray.y;
			color = 0xFF0000;
		}
		else
		{
			deltay.x /= fabsf(deltay.y);
			deltay.y /= fabsf(deltay.y);
			save.y = (floorf)(ray.y);
			save.x += (floorf)(ray.x) - ray.x;
			color = 0xff00;
		}
//		//printf("dfiawe%f, %f\n", deltay.x, deltay.y);
		hit = dda(world, ray, (t_vec){deltay.y, deltay.x});
		int color2;
		if (fabsf(delta.x) >= fabsf(delta.y))
		{
			delta.x /= fabsf(delta.x);
			delta.y /= fabsf(delta.x);
			//ray.x = (floorf)(ray.x);
			//ray.y += (floorf)(ray.y) - ray.y;
			color2 = 0xFF;
		}
		else
		{
			delta.x /= fabsf(delta.y);
			delta.y /= fabsf(delta.y);
			//ray.x += (floorf)(ray.x) - ray.x;
			//ray.y += floorf(ray.y);
			color2 = 0xFFFF;
		}
		int len1;
		int len2;
		len1 = distance(hit, playe->pos);
		hit2 = dda(world, ray, delta);
		len2 = distance(hit2, playe->pos);
		if (len1 < len2)
			draw_wall(world, playe, ray, hit, x, color);
		else
			draw_wall(world, playe, ray, hit2, x, color2);
		printf("%x\n", color);
		x++;
	}
}

void		render(t_data *data)
{
	void		*img;
	int			shit;
	t_world		*world;

	world = &data->world;
	img = mlx_new_image(data->mlx, WIN_W, WIN_H);
	world->screen = (int (*)[])mlx_get_data_addr(img, &shit, &shit, &shit);
	raycast(&data->world, &data->player);
//	printf("End\n");
	mlx_put_image_to_window(data->mlx, data->win, img, 0, 0);
	mlx_destroy_image(data->mlx, img);
}

t_vec		vec_rot(t_vec vec, float angle)
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
		data->player.pos.y += data->player.dir.y;
		data->player.pos.x += data->player.dir.x;
		printf("%f, %f\n", data->player.pos.x, data->player.pos.y);
		render(data);
	}
	if (keycode == 125)
	{
		data->player.pos.y -= data->player.dir.y;
		data->player.pos.x -= data->player.dir.x;
		render(data);
	}
	if (keycode == 124) {
		data->player.dir =  vec_rot(data->player.dir, -0.1);
		data->player.cam =  vec_rot(data->player.cam, -0.1);
		render(data);
	}
	if (keycode == 123)
	{
		data->player.dir =  vec_rot(data->player.dir, 0.1);
		data->player.cam =  vec_rot(data->player.cam, 0.1);
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
	data.player.pos = (t_vec){25, 8};
	data.player.dir = (t_vec){0, 1};
	data.player.cam = (t_vec){2, 0};
	data.mlx = mlx_init();
	data.win = mlx_new_window(data.mlx, WIN_W, WIN_H, "wolf3d");
	mlx_hook(data.win,2, 0, (int (*)())key_hook, &data);
	render(&data);
	mlx_loop(data.mlx);
}
