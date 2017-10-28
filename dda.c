/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmenigau <lmenigau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/28 18:10:12 by lmenigau          #+#    #+#             */
/*   Updated: 2017/10/28 19:35:21 by lmenigau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static float	dstman(t_vec a, t_vec b)
{
	return (fabsf(a.x - b.x) + fabsf(a.y - b.y));
}

static int		check(t_ray *ray, int flag)
{
	if (flag == 0 && ray->start.x - ray->dec >= 0 && ray->start.y >= 0 &&
			ray->start.x - ray->dec < 75 && ray->start.y < 22)
		return (1);
	else if (flag == 1 && ray->start.x >= 0 && ray->start.y - ray->dec >= 0 &&
			ray->start.x < 75 && ray->start.y - ray->dec < 22)
		return (1);
	return (0);
}

t_hit			dda2(t_world *world, t_ray *rayx, t_ray *rayy, t_vec pos)
{
	char	(*map)[75];
	t_vec	dist;
	t_ivec	flag;

	map = (char (*)[75])world->map;
	flag = (t_ivec){1, 1};
	while (flag.x && flag.y)
	{
		dist = (t_vec){dstman(pos, rayx->start), dstman(pos, rayy->start)};
		if (flag.x && dist.x < dist.y && (flag.x = check(rayx, 0)))
		{
			if (map[(int)rayx->start.y][(int)rayx->start.x - rayx->dec] != ' ')
				return ((t_hit){rayx->start, world->colors[rayx->dec]});
			rayx->start.x += rayx->delta.x;
			rayx->start.y += rayx->delta.y;
		}
		if (flag.y && dist.x >= dist.y && (flag.y = check(rayy, 1)))
		{
			if (map[(int)rayy->start.y - rayy->dec][(int)rayy->start.x] != ' ')
				return ((t_hit){rayy->start, world->colors[rayy->dec + 2]});
			rayy->start.x += rayy->delta.x;
			rayy->start.y += rayy->delta.y;
		}
	}
	return ((t_hit){{1000, 1000}, 0x00});
}
