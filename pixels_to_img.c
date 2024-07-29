/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixels_to_img.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maheleni <maheleni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 15:02:57 by maheleni          #+#    #+#             */
/*   Updated: 2024/07/29 15:13:57 by maheleni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void    fill_screen(t_map *map, int color)
{
    memset(map->img->pixels, color, map->img->width * map->img->height * sizeof(int32_t));
}

void	draw(t_map *map)
{
	t_view		view;
	int		i;

    fill_screen(map, 0xFFFFFF00);
	view = map->view;
	i = 0;
	while (i < map->height)
	{
		int j = 0;
		while (j < map->width)
		{
			float x = map->points[i][j].x;
			float y = map->points[i][j].y;
			float x_view = x * view.zoom + view.width_offset;
			float y_view = y * view.zoom + view.height_offset;
			printf("X: %f, Y: %f\n", x, y);
			printf("X: %f, Y: %f\n", x_view, y_view);
			if (x_view >= 0 && x_view <= WIDTH && y_view >= 0 && y_view <= HEIGHT)
			{
				printf("PRINTING: X: %f, Y: %f\n", x_view,y_view);
				if (map->points[i][j].height == 10)
					mlx_put_pixel(map->img, x_view, y_view, 0x00FF00FF);
				else
					mlx_put_pixel(map->img, x_view, y_view, 0xFF0000FF);
			}
			printf("%i of total %i\n", (i * map->width) + j, map->width * map->height);
			j++;
		}
		i++;
	}
	
}