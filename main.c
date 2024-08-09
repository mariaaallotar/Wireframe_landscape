/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maheleni <maheleni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 09:46:03 by maheleni          #+#    #+#             */
/*   Updated: 2024/08/09 15:54:32 by maheleni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	error(void)
{
	puts(mlx_strerror(mlx_errno));
	exit(EXIT_FAILURE);
}

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

static void	init_map(t_map *map, char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	//TODO handle wrong file or permissions error
	get_dimensions(fd, map);
	// printf("Height of map: %i\n", map->height);
	map->points = malloc (map->height * sizeof(t_point*));
	if (map->points == NULL)
		error();
	// printf("Init map malloc passed\n");
	close (fd);
	fd = open(file, O_RDONLY);
	map->smallest_x = INT32_MAX;
	map->smallest_y = INT32_MAX;
	map->biggest_x = INT32_MIN;
	map->biggest_y = INT32_MIN;
	parse_map(fd, map);
}

static mlx_t*	init_mlx(t_fdf *fdf)
{
	mlx_t		*mlx;
	mlx_image_t	*img;

	mlx = mlx_init(1, 1, "JUST TO INIT GLWF", false);
	if (!mlx)
        error();
	mlx_get_monitor_size(0, &(fdf->win_width), &(fdf->win_height));
	fdf->win_height -= 80;
	mlx_terminate(mlx);
	mlx = NULL;
	mlx = mlx_init(fdf->win_width, fdf->win_height, "FDF", false);
	if (!mlx)
        error();
	img = mlx_new_image(mlx, fdf->win_width, fdf->win_height);
	if (!img)
		error();
	fdf->img = img;
	return (mlx);
}

void	free_points(int row_index, t_map *map);

int	main(int argc, char *argv[])
{
	t_fdf	fdf;
	mlx_t	*mlx;

	if (argc != 2)
	{
		ft_printf("This program takes only one argument: a name of a file ending in '.fdf'.\n");
		return (1);
	}
	mlx = init_mlx(&fdf);
	init_map(&(fdf.map), argv[1]);
	// printf("Init map passed\n");
	isometric_transformation(&(fdf.map));
	// printf("Iso done\n");
	init_view(&fdf);
	// printf("View initialized\n");
	center_map(&(fdf));
	// printf("Map centered\n");
	draw_map(&fdf);
	// printf("Map drawn\n");
	add_hooks(mlx, &fdf);
	if (mlx_image_to_window(mlx, fdf.img, 0, 0) < 0)
        error();
	mlx_loop(mlx);

	//TODO
	// Optional, terminate will clean up any leftovers, this is just to demonstrate.
	mlx_delete_image(mlx, fdf.img);
	mlx_terminate(mlx);
	free_points(fdf.map.height - 1, &(fdf.map));
	return (EXIT_SUCCESS);
}
