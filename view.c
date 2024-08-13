/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   view.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maheleni <maheleni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 10:49:27 by maheleni          #+#    #+#             */
/*   Updated: 2024/08/13 13:21:26 by maheleni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	center_map(t_fdf *fdf)
{
	int	x_center;
	int	y_center;
	int	i;
	int	j;

	x_center = (fdf->map.smallest_x + fdf->map.biggest_x) / 2;
	y_center = (fdf->map.smallest_y + fdf->map.biggest_y) / 2;
	i = 0;
	while (i < fdf->map.height)
	{
		j = 0;
		while (j < fdf->map.width)
		{
			fdf->map.points[i][j].x += fdf->win_width / 2 - x_center;
			fdf->map.points[i][j].y += fdf->win_height / 2 - y_center;
			update_max_min_x_y(&(fdf->map.points[i][j]), &(fdf->map));
			j++;
		}
		i++;
	}
}

static int	width_zoom_factor(t_fdf *fdf)
{
	int	width_zoom;
	int	zoomed_x0;
	int	zoomed_x1;

	width_zoom = 1;
	zoomed_x0 = fdf->map.smallest_x;
	zoomed_x1 = fdf->map.biggest_x;
	while (abs(zoomed_x1 - zoomed_x0) < (fdf->win_width - 200))
	{
		width_zoom++;
		zoomed_x0 = fdf->map.biggest_x * width_zoom;
		zoomed_x1 = fdf->map.smallest_x * width_zoom;
	}
	return (width_zoom);
}

static int	height_zoom_factor(t_fdf *fdf)
{
	int	height_zoom;
	int	zoomed_y0;
	int	zoomed_y1;

	height_zoom = 1;
	zoomed_y0 = fdf->map.smallest_y;
	zoomed_y1 = fdf->map.biggest_y;
	while (abs(zoomed_y1 - zoomed_y0) < (fdf->win_height - 200))
	{
		height_zoom++;
		zoomed_y0 = fdf->map.biggest_y * height_zoom;
		zoomed_y1 = fdf->map.smallest_y * height_zoom;
	}
	return (height_zoom);
}

void	set_zoom_factor(t_fdf *fdf)
{
	int	width_zoom;
	int	height_zoom;

	width_zoom = width_zoom_factor(fdf);
	height_zoom = height_zoom_factor(fdf);
	if (height_zoom < width_zoom)
		fdf->view.zoom = height_zoom;
	else
		fdf->view.zoom = width_zoom;
}
