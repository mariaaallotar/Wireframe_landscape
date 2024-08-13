/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maheleni <maheleni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 11:55:31 by maheleni          #+#    #+#             */
/*   Updated: 2024/08/13 13:34:32 by maheleni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	free_points(int row_index, t_map *map)
{
	while (row_index >= 0)
	{
		if (map->points[row_index] == NULL)
		{
			row_index--;
			continue ;
		}
		if (&(map->points[row_index][0]) != NULL)
			free(&(map->points[row_index][0]));
		row_index--;
	}
	free(map->points);
}

void	terminate_mlx(t_fdf *fdf)
{
	mlx_delete_image(fdf->mlx, fdf->img);
	mlx_close_window(fdf->mlx);
	mlx_terminate(fdf->mlx);
}

void	fdf_mlx_error(t_fdf *fdf, int free_bol)
{
	ft_printf(mlx_strerror(mlx_errno));
	terminate_mlx(fdf);
	if (free_bol)
		free_points(fdf->map.height - 1, &(fdf->map));
	exit(EXIT_FAILURE);
}

void	error(t_fdf *fdf, char *str, int free_bol)
{
	perror(str);
	terminate_mlx(fdf);
	if (free_bol)
		free_points(fdf->map.height - 1, &(fdf->map));
	exit(EXIT_FAILURE);
}

void	exit_program(t_fdf *fdf)
{
	terminate_mlx(fdf);
	free_points(fdf->map.height - 1, &(fdf->map));
	exit(EXIT_SUCCESS);
}
