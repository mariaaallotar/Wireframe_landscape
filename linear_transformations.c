/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linear_transformations.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maheleni <maheleni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 09:53:43 by maheleni          #+#    #+#             */
/*   Updated: 2024/08/08 11:04:08 by maheleni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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
		j = 0;
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