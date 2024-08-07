/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maheleni <maheleni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 13:50:52 by maheleni          #+#    #+#             */
/*   Updated: 2024/08/07 14:51:45 by maheleni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
void	center_map(t_fdf *fdf);

void	move(int x, int y, t_fdf *fdf)
{
	int	i;
	int	j;

	i = 0;
	while (i < fdf->map.height)
	{
		j = 0;
		while (j < fdf->map.width)
		{
			fdf->map.points[i][j].x += x;
			fdf->map.points[i][j].y += y;
			update_max_min_x_y(&(fdf->map.points[i][j]), &(fdf->map));
			j++;
		}
		i++;
	}
	draw_map(fdf);
}

void	tilt_x(int deg, t_fdf *fdf)
{
	int	i;
	int	j;

	i = 0;
	while (i < fdf->map.height)
	{
		j = 0;
		while (j < fdf->map.width)
		{
			rotate_around_x(deg, &(fdf->map.points[i][j]));
			update_max_min_x_y(&(fdf->map.points[i][j]), &(fdf->map));
			j++;
		}
		i++;
	}
	draw_map(fdf);
}

void	tilt_y(int deg, t_fdf *fdf)
{
	int	i;
	int	j;

	i = 0;
	while (i < fdf->map.height)
	{
		j = 0;
		while (j < fdf->map.width)
		{
			rotate_around_y(deg, &(fdf->map.points[i][j]));
			update_max_min_x_y(&(fdf->map.points[i][j]), &(fdf->map));
			j++;
		}
		i++;
	}
	center_map(fdf);
	draw_map(fdf);
}

void	rotate(int deg, t_fdf *fdf)
{
	int	i;
	int	j;

	i = 0;
	while (i < fdf->map.height)
	{
		j = 0;
		while (j < fdf->map.width)
		{
			rotate_around_z(deg, &(fdf->map.points[i][j]));
			update_max_min_x_y(&(fdf->map.points[i][j]), &(fdf->map));
			j++;
		}
		i++;
	}
	draw_map(fdf);
}

// void	zoom(int zoom, t_fdf *fdf)
// {
// 	int		i;
// 	int		j;
// 	t_point	**points;

// 	fdf->view.zoom += zoom;
// 	points = fdf->map.points;
// 	i = 0;
// 	while (i < fdf->map.height)
// 	{
// 		j = 0;
// 		while (j < fdf->map.width)
// 		{
// 			points[i][j].x = points[i][j].x + fdf->view.zoom;
// 			points[i][j].y = points[i][j].y + fdf->view.zoom;
// 			points[i][j].z = points[i][j].z + fdf->view.zoom;
// 			update_max_min_x_y(&(points[i][j]), &(fdf->map));
// 			j++;
// 		}
// 		i++;
// 	}
// 	center_map(fdf);
// 	draw_map(fdf);
// }

void	random_translation(t_fdf *fdf)
{
	int	i;
	int	j;

	i = 0;
	while (i < fdf->map.height)
	{
		j = 0;
		while (j < fdf->map.width)
		{
			rotate_around_x(10, &(fdf->map.points[i][j]));
			rotate_around_y(50, &(fdf->map.points[i][j]));
			rotate_around_z(-70, &(fdf->map.points[i][j]));
			j++;
		}
		i++;
	}
	draw_map(fdf);
}

void	fdf_keyhook(mlx_key_data_t keydata, void *param)
{
	if (keydata.key == MLX_KEY_D && keydata.action == MLX_PRESS)
		move(40, 0, param);
	if (keydata.key == MLX_KEY_A && keydata.action == MLX_PRESS)
		move(-40, 0, param);
	if (keydata.key == MLX_KEY_W && keydata.action == MLX_PRESS)
		move(0, -40, param);
	if (keydata.key == MLX_KEY_S && keydata.action == MLX_PRESS)
		move(0, 40, param);
	if (keydata.key == MLX_KEY_1 && keydata.action == MLX_PRESS)
		rotate(2, param);
	if (keydata.key == MLX_KEY_2
		&& (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
		rotate(-2, param);
	if (keydata.key == MLX_KEY_UP && keydata.action == MLX_PRESS)
		tilt_x(2, param);
	if (keydata.key == MLX_KEY_DOWN && keydata.action == MLX_PRESS)
		tilt_x(-2, param);
	if (keydata.key == MLX_KEY_LEFT && keydata.action == MLX_PRESS)
		tilt_y(2, param);
	if (keydata.key == MLX_KEY_RIGHT && keydata.action == MLX_PRESS)
		tilt_y(-2, param);
	if (keydata.key == MLX_KEY_R && keydata.action == MLX_PRESS)
		random_translation(param);
}
