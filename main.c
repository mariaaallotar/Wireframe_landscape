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

void	add_hooks(mlx_t *mlx, t_map *map)
{
	mlx_key_hook(mlx, &fdf_keyhook, map);
	mlx_scroll_hook(mlx, &fdf_scrollhook, map);
}

static void	init_view(t_map *map)
{
	t_view	view;
	int		i;
	int		j;

	set_zoom_factor(&view, map);
	view.height_offset = 20;
	view.width_offset = WIDTH / 2;
	map->view = view;
	i = 0;
	while (i < map->height)
	{
		j = 0;
		while (j < map->width)
		{
			map->points[i][j].x = map->points[i][j].x * view.zoom + view.width_offset;
			map->points[i][j].y = map->points[i][j].y * view.zoom + view.height_offset;
			map->points[i][j].z = map->points[i][j].z * view.zoom + view.height_offset;
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

	int height = map->height;
	int width = map->width;

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

static mlx_t*	init_mlx(t_map *map)
{
	mlx_t		*mlx;
	mlx_image_t	*img;

	mlx = mlx_init(WIDTH, HEIGHT, "FDF", false);
	if (!mlx)
        error();
	img = mlx_new_image(mlx, WIDTH, HEIGHT);
	if (!img)
		error();
	map->img = img;
	return (mlx);
}

int	main(int argc, char *argv[])
{
	t_map		map;
	mlx_t		*mlx;

	if (argc != 2)
	{
		ft_printf("This program takes only one argument: a name of a file ending in '.fdf'.\n");
		return (1);
	}
	init_map(&map, argv[1]);
	init_view(&map);
	mlx = init_mlx(&map);
	isometric_transformation(&map);
	draw_map(&map);
	add_hooks(mlx, &map);
	if (mlx_image_to_window(mlx, map.img, 0, 0) < 0)
        error();
	mlx_loop(mlx);

	//TODO
	// Optional, terminate will clean up any leftovers, this is just to demonstrate.
	mlx_delete_image(mlx, map.img);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}