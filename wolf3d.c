/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmenigau <lmenigau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/09 03:50:26 by lmenigau          #+#    #+#             */
/*   Updated: 2022/11/25 05:08:08 by lomeniga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"
#include <stdlib.h>
#include <time.h>

static float	norme(t_vec vec)
{
	return (sqrtf(vec.x * vec.x + vec.y * vec.y));
}

static void		mlx_safe_init(t_data *data)
{
	int				bs;

	if ((data->mlx = mlx_init()) == NULL)
		exit(1);
	if ((data->win = mlx_new_window(data->mlx, WIN_W, WIN_H, "wolf3d")) == NULL)
		exit(1);
	if ((data->img = mlx_new_image(data->mlx, WIN_W, WIN_H)) == NULL)
		exit(1);
	if ((data->world.screen = (int (*)[])mlx_get_data_addr(data->img,
					&bs, &bs, &bs)) == NULL)
		exit(1);
}

int				main(void)
{
	t_data			data;
	static int		keys[MAX_KEY];

	mlx_safe_init(&data);
	data.keys = keys;
	data.world.map = init_world();
	srand((unsigned int)time(NULL));
	//srandomdev();
	data.world.colors = (int[4]){(int)random() >> 8, (int)random() >> 8,
		(int)random() >> 8, (int)random() >> 8};
	data.player.pos = (t_vec){10, 2};
	data.player.dir = vec_rot((t_vec){0, 1}, 0.05f);
	data.player.cam = vec_rot((t_vec){1.5f, 0}, 0.05f);
	data.player.ndir = norme(data.player.dir);
	place_hooks(&data);
	mlx_loop(data.mlx);
}
