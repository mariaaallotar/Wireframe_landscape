/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maheleni <maheleni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 09:46:03 by maheleni          #+#    #+#             */
/*   Updated: 2024/08/22 09:41:01 by maheleni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	init_view(t_fdf *fdf)
{
	t_view	view;
	t_point	**points;
	int		i;
	int		j;

	set_zoom_factor(fdf);
	view = fdf->view;
	points = fdf->map.points;
	i = 0;
	while (i < fdf->map.height)
	{
		j = 0;
		while (j < fdf->map.width)
		{
			points[i][j].x = points[i][j].x * view.zoom;
			points[i][j].y = points[i][j].y * view.zoom;
			points[i][j].z = points[i][j].z * view.zoom;
			update_max_min_x_y(&(points[i][j]), &(fdf->map));
			j++;
		}
		i++;
	}
}

static void	init_map(t_fdf *fdf, t_map *map, char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		error(fdf, file, 0);
	get_dimensions(fd, map, fdf);
	map->points = malloc (map->height * sizeof(t_point *));
	if (map->points == NULL)
		error(fdf, NULL, 0);
	close (fd);
	fd = open(file, O_RDONLY);
	map->smallest_x = INT32_MAX;
	map->smallest_y = INT32_MAX;
	map->biggest_x = INT32_MIN;
	map->biggest_y = INT32_MIN;
	parse_map(fd, map, fdf);
}

static mlx_t	*init_mlx(t_fdf *fdf)
{
	mlx_t		*mlx;
	mlx_image_t	*img;

	mlx = mlx_init(1, 1, "JUST TO INIT GLWF", false);
	if (!mlx)
		fdf_mlx_error(fdf, 0);
	mlx_get_monitor_size(0, &(fdf->win_width), &(fdf->win_height));
	fdf->win_height -= 80;
	mlx_terminate(mlx);
	mlx = NULL;
	mlx = mlx_init(fdf->win_width, fdf->win_height, "FDF", true);
	if (!mlx)
		fdf_mlx_error(fdf, 0);
	img = mlx_new_image(mlx, fdf->win_width, fdf->win_height);
	if (!img)
		fdf_mlx_error(fdf, 0);
	if (mlx_image_to_window(mlx, img, 10, 10) < 0)
		fdf_mlx_error(fdf, 1);
	fdf->img = img;
	fdf->mlx = mlx;
	return (mlx);
}

int	main(int argc, char *argv[])
{
	t_fdf	fdf;
	mlx_t	*mlx;

	if (argc != 2)
	{
		ft_printf("This program takes only one argument:"
			" a name of a file ending in '.fdf'.\n");
		return (1);
	}
	validate_file(argv[1]);
	mlx = init_mlx(&fdf);
	init_map(&fdf, &(fdf.map), argv[1]);
	isometric_transformation(&(fdf.map));
	init_view(&fdf);
	center_map(&(fdf));
	draw_map(&fdf, &(fdf.map));
	add_hooks(mlx, &fdf);
	mlx_loop(mlx);
	terminate_mlx(&fdf);
	free_points(fdf.map.height - 1, &(fdf.map));
	return (EXIT_SUCCESS);
}
