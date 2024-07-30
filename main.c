/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maheleni <maheleni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 09:46:03 by maheleni          #+#    #+#             */
/*   Updated: 2024/07/30 15:18:35 by maheleni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	init_line(t_line *line, t_point p0, t_point p1);
void	draw_line(t_line *line, t_map *map);

void	error(void)
{
	puts(mlx_strerror(mlx_errno));
	exit(EXIT_FAILURE);
}

void	init_view(t_view *view, t_map *map)
{
	set_zoom_factor(view, map);
	view->height_offset = 150;
	view->width_offset = 600;
}

int32_t	main(void)
{
	t_map	map;
	t_view	view;

	int fd = open("./test/42.fdf", O_RDONLY);
	get_dimensions(fd, &map);
	map.points = malloc (map.height * sizeof(t_point*));
	if (map.points == NULL)
		error();
	close (fd);
	fd = open("./test/42.fdf", O_RDONLY);
	parse_map(fd, &map);
	init_view(&view, &map);
	map.view = view;

	int i = 0;
	while (i < map.height)
	{
		int j = 0;
		while (j < map.width)
		{
			map.points[i][j].x = map.points[i][j].x * view.zoom + view.width_offset;
			map.points[i][j].y = map.points[i][j].y * view.zoom + view.height_offset;
			map.points[i][j].z = map.points[i][j].z * view.zoom + view.height_offset;
			j++;
		}
		i++;
	}
	
	// Start mlx
	mlx_t* mlx = mlx_init(WIDTH, HEIGHT, "Test", true);
	if (!mlx)
        error();
	
	mlx_key_hook(mlx, &fdf_keyhook, &map);
	mlx_scroll_hook(mlx, &fdf_scrollhook, &map);

	// Create a new image
	mlx_image_t* img = mlx_new_image(mlx, WIDTH, HEIGHT);
	if (!img)
		error();
	map.img = img;

	i = 0;
	while (i < map.height)
	{
		int j = 0;
		while (j < map.width)
		{
			isometric_transformation(&(map.points[i][j]));
			j++;
		}
		i++;
	}

	draw_map(&map);
	// t_line line;
	// init_line(&line, map.points[0][map.width - 2], map.points[0][0]);
	// draw_line(&line, &map);
	
	// Display an instance of the image
	if (mlx_image_to_window(mlx, img, 0, 0) < 0)
        error();

	mlx_loop(mlx);

	// Optional, terminate will clean up any leftovers, this is just to demonstrate.
	mlx_delete_image(mlx, img);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}