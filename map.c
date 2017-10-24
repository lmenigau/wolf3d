/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmenigau <lmenigau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/22 21:07:27 by lmenigau          #+#    #+#             */
/*   Updated: 2017/05/23 18:06:18 by lmenigau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*init_world()
{
	static char	map[50][50] = {
		{"xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx"},
		{"x                                                x"},
		{"x                                                x"},
		{"x                                                x"},
		{"x                            x                   x"},
		{"x                            x                   x"},
		{"x                            xxxxxxxxxx          x"},
		{"x                                                x"},
		{"x                                                x"},
		{"x                                                x"},
		{"x                                                x"},
		{"x                                                x"},
		{"x                                                x"},
		{"x          x                                     x"},
		{"x          x                                     x"},
		{"x      xxxxxxxxxxxxxxxxx xxxxx                   x"},
		{"x          x                 x                   x"},
		{"x          x  xxxxxxx        x          x        x"},
		{"x          x                 x          x        x"},
		{"x          x                 x          x        x"},
		{"x          x                            x        x"},
		{"x          x                 x          x        x"},
		{"x          x                 x          x        x"},
		{"x          x                 x          x        x"},
		{"x          x                 x                   x"},
		{"x          x                 x          x        x"},
		{"x          x                 x          x        x"},
		{"x          x     x  x        x          x        x"},
		{"x          x     x  x        x          x        x"},
		{"x          x     x  x        x          x        x"},
		{"x                xxxx                            x"},
		{"x                                                x"},
		{"x                                                x"},
		{"x                                                x"},
		{"x                                                x"},
		{"x               x                                x"},
		{"x               x xxxxxxxxxxxxxxxxxxxxxxx        x"},
		{"x     x x       x                                x"},
		{"x       x       xxxxxxxxxxxxxxxxxxxxxxxxxxx      x"},
		{"x     x x                                        x"},
		{"x                                                x"},
		{"x                                                x"},
		{"x                   x                            x"},
		{"x                                                x"},
		{"x            x  x    x                           x"},
		{"x                                                x"},
		{"x                                                x"},
		{"x                                                x"},
		{"x                                                x"},
		{"xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx"}};
	return ((char *)&map);
}

