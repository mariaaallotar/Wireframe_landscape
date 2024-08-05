/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maheleni <maheleni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 09:46:03 by maheleni          #+#    #+#             */
/*   Updated: 2024/07/31 14:19:13 by maheleni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	error(void)
{
	puts(mlx_strerror(mlx_errno));
	exit(EXIT_FAILURE);
}

void	add_hooks(mlx_t *mlx, t_fdf *fdf)
{
	mlx_key_hook(mlx, &fdf_keyhook, fdf);
	mlx_scroll_hook(mlx, &fdf_scrollhook, fdf);
}

static void	init_view(t_fdf *fdf)
{
	t_view	view;
	t_point	**points;
	int		i;
	int		j;

	set_zoom_factor(fdf);
	//TODO fix offsets
	// printf("After set zoom\n");
	view.height_offset = 20;
	view.width_offset = fdf->win_width / 2;
	fdf->view = view;
	points = fdf->map.points;
	i = 0;
	while (i < fdf->map.height)
	{
		// printf("i is %i, in init view\n", i);
		j = 0;
		while (j < fdf->map.width)
		{
			// printf("j is %i, in init view\n", j);
			// printf("First point memoryplace: %p", &(fdf->map.points[i][j]));
			points[i][j].x = points[i][j].x * view.zoom + view.width_offset;	//This segfaults
			points[i][j].y = points[i][j].y * view.zoom + view.height_offset;
			points[i][j].z = points[i][j].z * view.zoom + view.height_offset;
			j++;
		}
		i++;
	}
	// printf("Exiting init_view\n");
}

static void	init_map(t_map *map, char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	//TODO handle wrong file or permissions error
	get_dimensions(fd, map);



	int height = map->height;
	int width = map->width;
	// printf("Map height %i, width %i\n", map->height, map->width);


	map->points = malloc (map->height * sizeof(t_point*));
	if (map->points == NULL)
		error();
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


	printf("Monitor height %i, width %i\n", fdf->win_height, fdf->win_width);


	mlx = mlx_init(fdf->win_width, fdf->win_height, "FDF", false);
	if (!mlx)
        error();
	img = mlx_new_image(mlx, fdf->win_width, fdf->win_height);
	if (!img)
		error();
	fdf->img = img;
	return (mlx);
}
	//DEBUG
	void	init_line(t_line *line, t_point p0, t_point p1);
	void	draw_line(t_line *line, t_fdf *fdf);

int	main(int argc, char *argv[])
{
	t_fdf	fdf;
	mlx_t	*mlx;
	t_map	map;

	if (argc != 2)
	{
		ft_printf("This program takes only one argument: a name of a file ending in '.fdf'.\n");
		return (1);
	}
	mlx = init_mlx(&fdf);
	// printf("MLX initialized\n");


	fdf.map = map;
	init_map(&(fdf.map), argv[1]);


	// printf("Map initialized and parsed\n");
	init_view(&fdf);
	// printf("View initialized\n");
	isometric_transformation(&(fdf.map));
	// printf("Iso done\n");
	draw_map(&fdf);
	// printf("Map drawn\n");


	//DEBUG
	t_line	line;
	init_line(&line, fdf.map.points[1][1], fdf.map.points[5][5]);
	draw_line(&line, &fdf);
	// printf("Line drawn\n");

	add_hooks(mlx, &fdf);
	if (mlx_image_to_window(mlx, fdf.img, 0, 0) < 0)
        error();
	// printf("Image to window\n");
	mlx_loop(mlx);

	//TODO
	// Optional, terminate will clean up any leftovers, this is just to demonstrate.
	mlx_delete_image(mlx, fdf.img);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}