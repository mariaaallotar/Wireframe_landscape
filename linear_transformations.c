/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linear_transformations.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maheleni <maheleni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 09:53:43 by maheleni          #+#    #+#             */
/*   Updated: 2024/07/30 09:11:00 by maheleni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	set_zoom_factor(t_view *view, t_map *map)
{
	int	width_zoom;
	int	height_zoom;

	width_zoom = (WIDTH - (2 * 300)) / map->width;
	height_zoom = (HEIGHT - (2 * 300)) / map->height;
	if (height_zoom < width_zoom)
		view->zoom = height_zoom;
	else
		view->zoom = width_zoom;
}

void	rotate_around_x(float deg, t_point *point)
{
	float rad;
    float temp_y;
    float temp_z;

	rad = deg * (M_PI / 180);
	temp_z = sin(rad) * point->y + cos(rad) * point->z;
    temp_y = cos(rad) * point->y - sin(rad) * point->z;
	point->y = temp_y;
    point->z = temp_z;
}

void	rotate_around_y(float deg, t_point *point)
{
	float rad;
    float temp_x;
    float temp_z;

	rad = deg * (M_PI / 180);
	temp_x = cos(rad) * point->x + sin(rad) * point->z;
	temp_z = - sin(rad) * point->x + cos(rad) * point->z;
    point->x = temp_x;
    point->z = temp_z;
}

void	rotate_around_z(float deg, t_point *point)
{
	float rad = deg * (M_PI / 180);
    float temp_x = cos(rad) * point->x - sin(rad) * point->y;
    float temp_y = sin(rad) * point->x + cos(rad) * point->y;
    point->x = temp_x;
    point->y = temp_y;
}

void	isometric_transformation(t_point *point)
{
	rotate_around_z(45, point);
	rotate_around_x(35.264, point);
}