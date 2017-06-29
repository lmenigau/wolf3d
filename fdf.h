/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmenigau <lmenigau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/20 23:53:20 by lmenigau          #+#    #+#             */
/*   Updated: 2017/02/23 04:17:06 by lmenigau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <math.h>


# define WIN_WIDTH	1920
# define WIN_HEIGHT	1080

# define ABS(x)		((x) < 0 ? (-(x)): (x))

typedef struct	s_vec2
{
	int			x;
	int			y;
}				t_vec2;

int				ft_abs(int n);

void			plotline_octant_vec(int (*img)[WIN_WIDTH], t_vec2 p0, t_vec2 p1,
		int fsp, int color);
void			plotline_vec(int (*img)[WIN_WIDTH], t_vec2 p0, t_vec2 p1, int color);
#endif
