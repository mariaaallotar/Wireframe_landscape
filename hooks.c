/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maheleni <maheleni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 13:50:52 by maheleni          #+#    #+#             */
/*   Updated: 2024/08/12 11:55:28 by maheleni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	move(int x, int y, t_fdf *fdf)
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

static void	tilt_x(int deg, t_fdf *fdf)
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

static void	tilt_z(int deg, t_fdf *fdf)
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
	if (keydata.key == MLX_KEY_UP && keydata.action == MLX_PRESS)
		tilt_x(2, param);
	if (keydata.key == MLX_KEY_DOWN && keydata.action == MLX_PRESS)
		tilt_x(-2, param);
	if (keydata.key == MLX_KEY_LEFT && keydata.action == MLX_PRESS)
		tilt_z(2, param);
	if (keydata.key == MLX_KEY_RIGHT && keydata.action == MLX_PRESS)
		tilt_z(-2, param);
}

void	add_hooks(mlx_t *mlx, t_fdf *fdf)
{
	mlx_key_hook(mlx, &fdf_keyhook, fdf);
}
