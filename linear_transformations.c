/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linear_transformations.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maheleni <maheleni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 09:53:43 by maheleni          #+#    #+#             */
/*   Updated: 2024/08/07 14:06:03 by maheleni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	update_max_min_x_y(t_point *point, t_map *map)
{
	if (point->x < map->smallest_x)
		map->smallest_x = point->x;
	else if (point->x > map->biggest_x)
		map->biggest_x = point->x;
	if (point->y < map->smallest_y)
		map->smallest_y = point->y;
	else if (point->y > map->biggest_y)
		map->biggest_y = point->y;
}

void	set_zoom_factor(t_fdf *fdf)
{
	int	width_zoom;
	int	height_zoom;
	int	zoomed_x0;
	int	zoomed_x1;
	int	zoomed_y0;
	int	zoomed_y1;

	width_zoom = 1;
	zoomed_x0 = fdf->map.smallest_x;
	zoomed_x1= fdf->map.biggest_x;
	while (abs(zoomed_x1 - zoomed_x0) < (fdf->win_width - 200))
	{
		width_zoom++;
		zoomed_x0 = fdf->map.biggest_x * width_zoom;
		zoomed_x1 = fdf->map.smallest_x * width_zoom;
	}
	height_zoom = 1;
	zoomed_y0 = fdf->map.smallest_y;
	zoomed_y1 = fdf->map.biggest_y;
	while (abs(zoomed_y1 - zoomed_y0) < (fdf->win_height - 200))
	{
		height_zoom++;
		zoomed_y0 = fdf->map.biggest_y * height_zoom;
		zoomed_y1 = fdf->map.smallest_y * height_zoom;
	}
	if (height_zoom < width_zoom)
		fdf->view.zoom = height_zoom;
	else
		fdf->view.zoom = width_zoom;
}

/*
* Rotates from the current position!
*/
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

/*
* Rotates from the current position!
*/
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

/*
* Rotates from the current position!
*/
void	rotate_around_z(float deg, t_point *point)
{
	float rad = deg * (M_PI / 180);
    float temp_x = cos(rad) * point->x - sin(rad) * point->y;
    float temp_y = sin(rad) * point->x + cos(rad) * point->y;
    point->x = temp_x;
    point->y = temp_y;
}

void	isometric_transformation(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	while (i < map->height)
	{
		int j = 0;
		while (j < map->width)
		{
			rotate_around_z(45, &(map->points[i][j]));
			rotate_around_x(35.264, &(map->points[i][j]));
			update_max_min_x_y(&(map->points[i][j]), map);
			j++;
		}
		i++;
	}
}