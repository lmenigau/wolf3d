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
# include "mlx.h"

# define	WIN_W	1920
# define	WIN_H	1080

typedef struct	s_ivec
{
	int		x;
	int		y;
}				t_ivec;

typedef struct	s_vec
{
	float		x;
	float		y;
}				t_vec;

typedef struct	s_player
{
	t_vec		pos;
	t_vec		cam;
	t_vec		dir;
}				t_player;

typedef struct	s_world
{
	t_vec	size;
	char	*map;
	int		(*screen)[WIN_W];
}				t_world;

typedef struct	s_data
{
	void		*mlx;
	void		*win;
	t_world		world;
	t_player	player;
}				t_data;

char	*init_world();
#endif
