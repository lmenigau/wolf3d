/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmenigau <lmenigau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/09 03:52:26 by lmenigau          #+#    #+#             */
/*   Updated: 2017/05/22 21:08:55 by lmenigau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_H
# define WOLF3D_H

# include <math.h>
# include <sys/time.h>
# include "mlx.h"

# define WIN_W			1920
# define WIN_H			1080

# define H_WIN_W		(1920 / 2)
# define H_WIN_H		(1080 / 2)

# define MAX_KEY		280

typedef struct	s_ivec
{
	int			x;
	int			y;
}				t_ivec;

typedef struct	s_vec
{
	float		x;
	float		y;
}				t_vec;

typedef struct	s_hit
{
	t_vec		hit;
	int			color;
}				t_hit;

typedef struct	s_ray
{
	t_vec		start;
	t_vec		delta;
	int			dec;
}				t_ray;

typedef struct	s_player
{
	t_vec		pos;
	t_vec		cam;
	t_vec		dir;
	float		ndir;
}				t_player;

typedef struct	s_world
{
	int			*colors;
	t_vec		size;
	char		*map;
	int			(*screen)[WIN_W];
	int			(*debug)[WIN_W];
}				t_world;

typedef struct	s_data
{
	void		*mlx;
	void		*win;
	void		*img;
	void		*wind;
	t_world		world;
	int			*keys;
	t_player	player;
	int			pad;
}				t_data;

char			*init_world();
#endif
