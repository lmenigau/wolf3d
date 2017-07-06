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
		{"x                           x                    x"},
		{"x                                                x"},
		{"x                                                x"},
		{"x                                                x"},
		{"x                                                x"},
		{"x                                                x"},
		{"x             xxxxxxxxxx  xxxxxx                 x"},
		{"x             x                x                 x"},
		{"x             x                x                 x"},
		{"x             x                x                 x"},
		{"x             x                x                 x"},
		{"x             x                x                 x"},
		{"x                    xx                          x"},
		{"x                    xx        x                 x"},
		{"x             x                                  x"},
		{"x             x                x                 x"},
		{"x             x                x                 x"},
		{"x             x                x                 x"},
		{"x             x                x                 x"},
		{"x             x                x                 x"},
		{"x             xxxxxx xxxx xxxxxx                 x"},
		{"x                                                x"},
		{"x                                                x"},
		{"x                                                x"},
		{"x                                                x"},
		{"x                                                x"},
		{"x                                                x"},
		{"x                                                x"},
		{"x                                                x"},
		{"x                                                x"},
		{"x                                                x"},
		{"x                                                x"},
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

