/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmenigau <lmenigau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/28 18:14:07 by lmenigau          #+#    #+#             */
/*   Updated: 2017/11/01 10:23:31 by lmenigau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

t_vec			vec_rot(t_vec vec, float angle)
{
	t_vec	res;

	res.x = vec.x * cosf(angle) - vec.y * sinf(angle);
	res.y = vec.x * sinf(angle) + vec.y * cosf(angle);
	return (res);
}

static int		check(int y, int x)
{
	return (x >= 0 && y >= 0 && y < 22 && x < 75);
}

static t_vec	collision(const char (*map)[75], t_vec pos, t_vec velo)
{
	if (check(pos.y, pos.x + velo.x)
			&& map[(int)pos.y][(int)(pos.x + velo.x)] == ' ')
		pos.x += velo.x;
	if (check(pos.y + velo.y, pos.x)
			&& map[(int)(pos.y + velo.y)][(int)pos.x] == ' ')
		pos.y += velo.y;
	return (pos);
}

void			key_moves(t_data *data)
{
	t_vec	velo;
	char	(*map)[75];

	map = (char (*)[75])data->world.map;
	velo = (t_vec){data->player.dir.x * .2f, data->player.dir.y * .2f};
	if (data->keys[126])
		data->player.pos = collision(map, data->player.pos, velo);
	velo = (t_vec){ -velo.x, -velo.y};
	if (data->keys[125])
		data->player.pos = collision(map, data->player.pos, velo);
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
