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
		{"x                                                x"},
		{"x                                                x"},
		{"x                                                x"},
		{"x                                                x"},
		{"x                                                x"},
		{"x                                                x"},
		{"x       |                    I                   x"},
		{"x       |                    I                   x"},
		{"x       |                    I                   x"},
		{"x       |                    I                   x"},
		{"x       |                    I                   x"},
		{"x       |                    I                   x"},
		{"x       |                    I                   x"},
		{"x       |                    I                   x"},
		{"x       |                    I                   x"},
		{"x       |                    I                   x"},
		{"x       |                    I                   x"},
		{"x       |                                        x"},
		{"x       ============   = ==== =====|             x"},
		{"x                                  |             x"},
		{"x                                  |             x"},
		{"x           yyytyyyyyyyyyyyyyy     |             x"},
		{"x              t                   |             x"},
		{"x              t                   |             x"},
		{"x              t                   |             x"},
		{"x              t                   |             x"},
		{"x              t                   |             x"},
		{"x              t                   |             x"},
		{"x              t        yyyy       |             x"},
		{"x              t        yyyy       |             x"},
		{"x              t        yyyy       |             x"},
		{"x              t        yyyy       |             x"},
		{"x              t                   |             x"},
		{"x              t                   |             x"},
		{"x              t                   |             x"},
		{"x              t                   |             x"},
		{"x              t                   |             x"},
		{"x              t                   |             x"},
		{"x                                                x"},
		{"x                                                x"},
		{"x                                                x"},
		{"x                                                x"},
		{"x                                                x"},
		{"x                                                x"},
		{"x                                                x"},
		{"xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx"}};
	return ((char *)&map);
}

