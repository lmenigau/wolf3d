/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmenigau <lmenigau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/28 18:14:07 by lmenigau          #+#    #+#             */
/*   Updated: 2017/10/28 18:15:32 by lmenigau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

t_vec	vec_rot(t_vec vec, float angle)
{
	t_vec	res;

	res.x = vec.x * cosf(angle) - vec.y * sinf(angle);
	res.y = vec.x * sinf(angle) + vec.y * cosf(angle);
	return (res);
}

void	key_moves(t_data *data)
{
	if (data->keys[126])
	{
		data->player.pos.y += data->player.dir.y * 0.2f;
		data->player.pos.x += data->player.dir.x * 0.2f;
	}
	if (data->keys[125])
	{
		data->player.pos.y -= data->player.dir.y * 0.2f;
		data->player.pos.x -= data->player.dir.x * 0.2f;
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
