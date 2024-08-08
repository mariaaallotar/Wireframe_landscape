/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maheleni <maheleni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 13:50:52 by maheleni          #+#    #+#             */
/*   Updated: 2024/08/08 11:23:11 by maheleni         ###   ########.fr       */
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
	//centering does not work
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
	center_map(fdf);
	draw_map(fdf);
}

static void	tilt_y(int deg, t_fdf *fdf)
{
	//centering does not work
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

static void	rotate(int deg, t_fdf *fdf)
{
	//does not rotate the way we expect now
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

static void	random_translation(t_fdf *fdf)
{
	//actually have this?
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
	//TODO check that all keys work the way as expected
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
	if (keydata.key == MLX_KEY_2 && keydata.action == MLX_PRESS)
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

void	add_hooks(mlx_t *mlx, t_fdf *fdf)
{
	mlx_key_hook(mlx, &fdf_keyhook, fdf);
}
