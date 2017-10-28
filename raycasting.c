/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmenigau <lmenigau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/28 18:11:14 by lmenigau          #+#    #+#             */
/*   Updated: 2017/10/28 19:29:16 by lmenigau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

float	distance(t_vec a, t_vec b)
{
	t_vec	total;

	total.x = fabsf(a.x - b.x);
	total.y = fabsf(a.y - b.y);
	return (sqrtf(total.x * total.x + total.y * total.y));
}

t_vec	ray_vector(t_player *play, int x)
{
	t_vec	ray;

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
	t_ray	rayx;
	t_ray	rayy;
	t_hit	hit;

	col = 0;
	while (col < WIN_W)
	{
		ray = ray_vector(play, col);
		build_ray(play->pos, ray, &rayx, &rayy);
		hit = dda2(world, &rayx, &rayy, play->pos);
		draw_wall(world,
				distance(hit.hit,
					play->pos) * play->ndir / distance(ray, play->pos),
				col, hit.color);
		col++;
	}
}
