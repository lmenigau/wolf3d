/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmenigau <lmenigau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/28 18:10:16 by lmenigau          #+#    #+#             */
/*   Updated: 2022/11/25 05:06:47 by lomeniga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"
#include <stddef.h>

static char	*ft_itoa(char *str, long n)
{
	long		pow;
	long		len;

	len = 1;
	pow = n;
	while (pow /= 10)
		len++;
	if (n < 0)
		len++;
	else
		n = -n;
	str[len--] = '\0';
	while (len >= 0)
	{
		str[len] = -(n % 10) + '0';
		n /= 10;
		if (n == 0 && len == 1)
			str[--len] = '-';
		len--;
	}
	return (str);
}

void		fps_counter(t_data *data)
{
	static struct timeval	last;
	static long				frames;
	struct timeval			current;
	static char				str[30];

	if (last.tv_sec == 0)
		gettimeofday(&last, NULL);
	frames++;
	gettimeofday(&current, NULL);
	if ((current.tv_usec - last.tv_usec) +
			(current.tv_sec - last.tv_sec) * 1000000 > 500000)
	{
		ft_itoa(str, frames * 1000000 / ((current.tv_usec - last.tv_usec)
					+ (current.tv_sec - last.tv_sec) * 1000000));
		last = current;
		frames = 0;
	}
	mlx_string_put(data->mlx, data->win, 10, 10, 0xFFFFFF, str);
}

void		draw_wall(t_world *world, float lenray, int col, int color)
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
		screen[i][col] = 0xC4D8E2;
	y--;
	while (++y < max)
		screen[y][col] = color;
	y--;
	while (++y < WIN_H)
		screen[y][col] = 0x4F7942;
}
