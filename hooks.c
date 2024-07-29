/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maheleni <maheleni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 13:50:52 by maheleni          #+#    #+#             */
/*   Updated: 2024/07/29 15:12:05 by maheleni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void    move(int x, int y, t_map *map)
{
    int i = 0;
	while (i < map->height)
	{
		int j = 0;
		while (j < map->width)
		{
			map->points[i][j].x += x;
            map->points[i][j].y += y;
			j++;
		}
		i++;
	}
    draw(map);
}

void    rotate(int deg, t_map *map)
{
    printf("Kukkuu\n");
}

void    fdf_keyhook(mlx_key_data_t keydata, void* param)
{
    if (keydata.key == MLX_KEY_RIGHT && keydata.action == MLX_REPEAT)
        move(1, 0, param);
    if (keydata.key == MLX_KEY_LEFT && keydata.action == MLX_REPEAT)
        move(-1, 0, param);
    if (keydata.key == MLX_KEY_UP && keydata.action == MLX_REPEAT)
        move(0, -1, param);
    if (keydata.key == MLX_KEY_DOWN && keydata.action == MLX_REPEAT)
        move(0, 1, param);
    if (keydata.key == MLX_KEY_1 && keydata.action == MLX_REPEAT)
        rotate(2, param);
    if (keydata.key == MLX_KEY_2 && keydata.action == MLX_REPEAT)
        rotate(-2, param);
}
