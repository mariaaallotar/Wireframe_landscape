/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixels_to_img.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maheleni <maheleni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 15:02:57 by maheleni          #+#    #+#             */
/*   Updated: 2024/07/30 15:21:00 by maheleni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void    fill_screen(t_map *map, int color)
{
    memset(map->img->pixels, color, map->img->width * map->img->height * sizeof(int32_t));
}

// void	draw(t_map *map)
// {
// 	t_view		view;
// 	int		i;

//     fill_screen(map, 0xFFFFFF00);
// 	view = map->view;
// 	i = 0;
// 	while (i < map->height)
// 	{
// 		int j = 0;
// 		while (j < map->width)
// 		{
// 			float x = map->points[i][j].x;
// 			float y = map->points[i][j].y;
// 			// printf("X: %f, Y: %f\n", x, y);
// 			if (x >= 0 && x<= WIDTH && y >= 0 && y <= HEIGHT)
// 			{
// 				// printf("PRINTING: X: %f, Y: %f\n", x,y);
// 				if (map->points[i][j].height == 10)
// 					mlx_put_pixel(map->img, x, y, 0x00FF00FF);
// 				else
// 					mlx_put_pixel(map->img, x, y, 0xFF0000FF);
// 			}
// 			// printf("%i of total %i\n", (i * map->width) + j, map->width * map->height);
// 			j++;
// 		}
// 		i++;
// 	}
// }

void	draw_high_line(t_line *line, t_map *map)
{
	printf("In draw_high_line\n");
    if (line->dx < 0)
	{
        line->xi = -1;
        line->dx = -line->dx;
	}
    while (line->y0 < line->y1) // <= ??
	{
		if (line->x0 >= 0 && line->x0 <= WIDTH && line->y0 >= 0 && line->y0 <= HEIGHT)
		{
			printf("PRINTING: %d %d\n", line->x0, line->y0);
        	mlx_put_pixel(map->img, line->x0, line->y0, 0xFFFFFFFF);
		}
        if (line->d > 0)
		{
			line->x += line->xi;
            line->d += (2 * (line->dx - line->dy));
		}
        else
            line->d += 2 * line->dx;
		(line->y0)++;
	}
}

void	draw_low_line(t_line *line, t_map *map)
{
	printf("In draw_low_line\n");
    if (line->dy < 0)
	{
        line->yi = -1;
        line->dy = -line->dy;
	}
    while (line->x0 < line->x1) // <= ??
	{
		if (line->x >= 0 && line->x <= WIDTH && line->y >= 0 && line->y <= HEIGHT)
        	mlx_put_pixel(map->img, line->x, line->y, 0xFFFFFFFF);
        if (line->d > 0)
		{
			line->y += line->yi;
            line->d += (2 * (line->dy - line->dx));
		}
        else
            line->d += 2 * line->dy;
		line->x0 += 1;
	}
}

void	swap_p0_and_p1(t_line *line)
{
	float	temp_x0;
	float	temp_y0;

	temp_x0 = line->x0;
	temp_y0 = line->y0;
	line->x0 = line->x1;
	line->y0 = line->y1;
	line->x1 = temp_x0;
	line->y1 = temp_y0;
}

void	draw_line(t_line *line, t_map *map)
{
	if (abs(line->y1 - line->y0) < abs(line->x1 - line->x0))
	{
        if (line->x0 > line->x1)
		{
			printf("In line->x0 > line->x1\n");
			swap_p0_and_p1(line);
            draw_low_line(line, map);
		}
        else
            draw_low_line(line, map);
	}
    else
	{
        if (line->y0 > line->y1)
		{
			printf("In line->y0 > line->y1\n");
			swap_p0_and_p1(line);
			draw_high_line(line, map);
		}
        else
            draw_high_line(line, map);
	}
}

void	init_line(t_line *line, t_point p0, t_point p1)
{
	line->x0 = p0.x;
	line->y0 = p0.y;
	line->x1 = p1.x;
	line->y1 = p1.y;
	line->dx = line->x1 - line->x0;
	line->dy = line->y1 - line->y0;
	line->x = line->x0;
	line->xi = 1;
	line->y = line->y0;
    line->yi = 1;
	line->d = (2 * line->dy) - line->dx;
}

void	draw_map(t_map *map)
{
	int		i;
	int		j;
	t_line	line;

    fill_screen(map, 0xFFFFFF00);
	i = 0;
	while (i < map->height)
	{
		j = 0;
		while (j < map->width)
		{
			if (!map->points[i][j].right_edge)
			{
				init_line(&line, map->points[i][j], map->points[i][j + 1]);
				draw_line(&line, map);
			}
			if (!map->points[i][j].bottom_edge)
			{
				init_line(&line, map->points[i][j], map->points[i + 1][j]);
				draw_line(&line, map);
			}
			j++;
		}
		i++;
	}
}
