/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maheleni <maheleni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 13:50:52 by maheleni          #+#    #+#             */
/*   Updated: 2024/08/13 13:49:45 by maheleni         ###   ########.fr       */
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
	draw_map(fdf, &(fdf->map));
}

static void	tilt(int x_deg, int y_deg, t_fdf *fdf)
{
	int	i;
	int	j;

	i = 0;
	while (i < fdf->map.height)
	{
		j = 0;
		while (j < fdf->map.width)
		{
			if (x_deg != 0)
				rotate_around_x(x_deg, &(fdf->map.points[i][j]));
			else if (y_deg != 0)
				rotate_around_y(y_deg, &(fdf->map.points[i][j]));
			update_max_min_x_y(&(fdf->map.points[i][j]), &(fdf->map));
			j++;
		}
		i++;
	}
	draw_map(fdf, &(fdf->map));
}

static void	fdf_closehook(void *param)
{
	exit_program(param);
}

static void	fdf_keyhook(mlx_key_data_t keydata, void *param)
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
		tilt(2, 0, param);
	if (keydata.key == MLX_KEY_DOWN && keydata.action == MLX_PRESS)
		tilt(-2, 0, param);
	if (keydata.key == MLX_KEY_LEFT && keydata.action == MLX_PRESS)
		tilt(0, 2, param);
	if (keydata.key == MLX_KEY_RIGHT && keydata.action == MLX_PRESS)
		tilt(0, -2, param);
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		exit_program(param);
}

void	add_hooks(mlx_t *mlx, t_fdf *fdf)
{
	mlx_key_hook(mlx, &fdf_keyhook, fdf);
	mlx_close_hook(mlx, &fdf_closehook, fdf);
}
