/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plotline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmenigau <lmenigau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/20 23:52:30 by lmenigau          #+#    #+#             */
/*   Updated: 2017/05/09 05:17:31 by lmenigau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	plotline_octant_vec(int (*img)[WIN_WIDTH], t_vec2 p0, t_vec2 p1,
		int fsp)
{
	int		dx;
	int		dy;
	int		d;
	int		x;
	int		y;

	dx = p1.x - p0.x;
	dy = p1.y - p0.y;
	d = 2 * dy - dx;
	x = p0.x;
	y = p0.y;
	while (x < p1.x)
	{
		if (fsp == 1)
			img[ABS(x)][ABS(y)] = 0x00FFFFFF;
		else
			img[ABS(y)][ABS(x)] = 0x00FFFFFF;
		if (d > 0)
		{
			y++;
			d = d - 2 * dx;
		}
		d = d + 2 * dy;
		x++;
	}
}

void	plotline_vec(int (*img)[WIN_WIDTH], t_vec2 p0, t_vec2 p1)
{
	int		fsp;

	if (p0.y > p1.y)
	{
		p0.y = -p0.y;
		p1.y = -p1.y;
	}
	fsp = 0;
	if (p0.x > p1.x)
	{
		p0.x = -p0.x;
		p1.x = -p1.x;
	}
	if (p1.x - p0.x < p1.y - p0.y)
	{
		ft_swap(&(p0.x), &(p0.y));
		ft_swap(&(p1.x), &(p1.y));
		fsp = 1;
	}
	plotline_octant_vec(img, p0, p1, fsp);
}
