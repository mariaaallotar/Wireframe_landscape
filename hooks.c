/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maheleni <maheleni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 13:50:52 by maheleni          #+#    #+#             */
/*   Updated: 2024/07/30 15:19:00 by maheleni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	move(int x, int y, t_map *map)
{
	int	i;
	int	j;

	i = 0;
	while (i < map->height)
	{
		j = 0;
		while (j < map->width)
		{
			map->points[i][j].x += x;
			map->points[i][j].y += y;
			j++;
		}
		i++;
	}
	draw_map(map);
}

void	rotate(int deg, t_map *map)
{
	int	i;
	int	j;

	i = 0;
	while (i < map->height)
	{
		j = 0;
		while (j < map->width)
		{
			rotate_around_z(deg, &(map->points[i][j]));
			j++;
		}
		i++;
	}
	draw_map(map);
}

void	zoom(int zoom, t_map *map)
{
	map->view.zoom += zoom;
	draw_map(map);
}

void	fdf_keyhook(mlx_key_data_t keydata, void *param)
{
	if (keydata.key == MLX_KEY_RIGHT
		&& (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
		move(5, 0, param);
	if (keydata.key == MLX_KEY_LEFT
		&& (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
		move(-5, 0, param);
	if (keydata.key == MLX_KEY_UP
		&& (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
		move(0, -5, param);
	if (keydata.key == MLX_KEY_DOWN
		&& (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
		move(0, 5, param);
	if (keydata.key == MLX_KEY_1
		&& (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
		rotate(2, param);
	if (keydata.key == MLX_KEY_2
		&& (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
		rotate(-2, param);
}

void	fdf_scrollhook(double xdelta, double ydelta, void* param)
{
	if (ydelta > 0)
		zoom(1, param);
	else if (ydelta < 0)
		zoom(-1, param);
}