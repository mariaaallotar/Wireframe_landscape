/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linear_transformations.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maheleni <maheleni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 09:53:43 by maheleni          #+#    #+#             */
/*   Updated: 2024/07/28 12:00:13 by maheleni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	set_zoom_factor(t_map *map)
{
	// int	width_zoom;
	// int	height_zoom;

	// width_zoom = map->width / (WIDTH - (2 * 50));
	// height_zoom = map->height / (HEIGHT - (2 * 50));
	// if (height_zoom < width_zoom)
	// 	map->zoom = height_zoom;
	// else
	// 	map->zoom = width_zoom;
	map->zoom = 20;
}

void	rotate_arund_z(int deg, t_point *point)
{
    point->x = cos(deg) * point->x + -sin(deg) * point->y;
    point->y = sin(deg) * point->x + cos(0) * point->y;
}

void	isometric_transformation(t_point *point)
{
	rotate_arund_z(44, point);
    point->y = sqrt(3)/3 * point->y + -(sqrt(6)/3) * point->z;
    point->z = sqrt(6)/3 * point->y + -(sqrt(3)/3) * point->z;
}