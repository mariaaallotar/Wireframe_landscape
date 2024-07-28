/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maheleni <maheleni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 09:46:03 by maheleni          #+#    #+#             */
/*   Updated: 2024/07/28 11:58:07 by maheleni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	error(void)
{
	puts(mlx_strerror(mlx_errno));
	exit(EXIT_FAILURE);
}

// t_map*	read_map(int fd, t_map *map)
// {
// 	get_dimensions(fd, map);
// 	int width = map->width;		//DEBUG
// 	int height = map->height;	//DEBUG
// 	map->points = malloc (map->width * map->height * sizeof(t_point));
// 	if (map->points == NULL)
// 		error();
// 	parse_map(fd, map);
// 	return (map);
// }

int32_t	main(void)
{
	t_map map;

	int fd = open("./test/42.fdf", O_RDONLY);
	get_dimensions(fd, &map);
	map.points = malloc (map.height * sizeof(t_point*));
	if (map.points == NULL)
		error();
	close (fd);
	fd = open("./test/42.fdf", O_RDONLY);
	parse_map(fd, &map);
	printf("X: %f, y: %f, z: %f\n", map.points[8][6].x, map.points[8][6].y, map.points[8][6].z);
	set_zoom_factor(&map);

	// Start mlx
	mlx_t* mlx = mlx_init(WIDTH, HEIGHT, "Test", true);
	if (!mlx)
        error();

	// Create a new image
	mlx_image_t* img = mlx_new_image(mlx, WIDTH, HEIGHT);
	if (!img)
		error();

	// Set every pixel to white
	memset(img->pixels, 255, img->width * img->height * sizeof(int32_t));

	int i = 0;
	int offset = 600;
	while (i < map.height)
	{
		int j = 0;
		while (j < map.width)
		{
			isometric_transformation(&(map.points[i][j]));
			printf("X: %f, Y: %f\n", (map.points[i][j].x), (map.points[i][j].y));
			printf("X: %f, Y: %f\n", (map.points[i][j].x * map.zoom + offset), (map.points[i][j].y * map.zoom + offset));
			if ((map.points[i][j].x * map.zoom + offset) >= 0 && ((map.points[i][j].x * map.zoom + offset) <= WIDTH) && ((map.points[i][j].y * map.zoom + offset) >= 0) && ((map.points[i][j].y * map.zoom + offset) <= HEIGHT))
			{
				printf("PRINTING: X: %f, Y: %f\n", (map.points[i][j].x * map.zoom +offset), (map.points[i][j].y * map.zoom + offset));
				mlx_put_pixel(img, (map.points[i][j].x * map.zoom +offset), (map.points[i][j].y * map.zoom + offset), 0xFF0000FF);
			}
			printf("%i of total %i\n", (i * map.width) + j, map.width * map.height);
			j++;
		}
		i++;
	}

	// Display an instance of the image
	if (mlx_image_to_window(mlx, img, 0, 0) < 0)
        error();

	mlx_loop(mlx);

	// Optional, terminate will clean up any leftovers, this is just to demonstrate.
	mlx_delete_image(mlx, img);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}