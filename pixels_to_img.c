/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixels_to_img.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maheleni <maheleni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 15:02:57 by maheleni          #+#    #+#             */
/*   Updated: 2024/08/13 13:55:36 by maheleni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	fill_screen(t_fdf *fdf, int color)
{
	mlx_image_t	*img;

	img = fdf->img;
	ft_memset(img->pixels, color, img->width * img->height * sizeof(int32_t));
}

static void	draw_high_line(t_line *line, t_fdf *fdf)
{
	if (line->dx < 0)
	{
		line->xi = -1;
		line->dx = -line->dx;
	}
	line->d = (2 * line->dx) - line->dy;
	line->x = line->x0;
	line->y = line->y0;
	while (line->y <= line->y1)
	{
		if (line->x >= 0 && line->x < fdf->win_width
			&& line->y >= 0 && line->y < fdf->win_height)
		{
			mlx_put_pixel(fdf->img, line->x, line->y, 0xFFFFFFFF);
		}
		if (line->d > 0)
		{
			line->x += line->xi;
			line->d += (2 * (line->dx - line->dy));
		}
		else
			line->d += 2 * line->dx;
		line->y += 1;
	}
}

static void	draw_low_line(t_line *line, t_fdf *fdf)
{
	if (line->dy < 0)
	{
		line->yi = -1;
		line->dy = -line->dy;
	}
	line->d = (2 * line->dy) - line->dx;
	line->x = line->x0;
	line->y = line->y0;
	while (line->x <= line->x1)
	{
		if (line->x >= 0 && line->x < fdf->win_width
			&& line->y >= 0 && line->y < fdf->win_height)
		{
			mlx_put_pixel(fdf->img, line->x, line->y, 0xFFFFFFFF);
		}
		if (line->d > 0)
		{
			line->y += line->yi;
			line->d += (2 * (line->dy - line->dx));
		}
		else
			line->d += 2 * line->dy;
		line->x += 1;
	}
}

static void	draw_line(t_line *line, t_fdf *fdf)
{
	if (abs(line->dy) < abs(line->dx))
	{
		if (line->x0 > line->x1)
		{
			swap_p0_and_p1(line);
			line->dx = line->x1 - line->x0;
			line->dy = line->y1 - line->y0;
			draw_low_line(line, fdf);
		}
		else
			draw_low_line(line, fdf);
	}
	else
	{
		if (line->y0 > line->y1)
		{
			swap_p0_and_p1(line);
			line->dx = line->x1 - line->x0;
			line->dy = line->y1 - line->y0;
			draw_high_line(line, fdf);
		}
		else
			draw_high_line(line, fdf);
	}
}

void	draw_map(t_fdf *fdf, t_map *map)
{
	int		i;
	int		j;
	t_line	line;

	fill_screen(fdf, 0xFFFFFF00);
	i = 0;
	while (i < fdf->map.height)
	{
		j = 0;
		while (j < fdf->map.width)
		{
			if (!fdf->map.points[i][j].right_edge)
			{
				init_line(&line, map->points[i][j], map->points[i][j + 1]);
				draw_line(&line, fdf);
			}
			if (!fdf->map.points[i][j].bottom_edge)
			{
				init_line(&line, map->points[i][j], map->points[i + 1][j]);
				draw_line(&line, fdf);
			}
			j++;
		}
		i++;
	}
}
