/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maheleni <maheleni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 09:46:03 by maheleni          #+#    #+#             */
/*   Updated: 2024/08/07 15:04:19 by maheleni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	center_map(t_fdf *fdf)
{
	// int	i;
	// int	j;
	// int	move_x;
	// int	move_y;

	// move_x = 5;
	// while(move_x + fdf->map.biggest_x < (fdf->win_width / 2 + (fdf->map.biggest_x - fdf->map.smallest_x) / 2))
	// 	move_x += 5;
	// move_y = 3;
	// while(move_y + fdf->map.biggest_y < (fdf->win_height / 2 + (fdf->map.biggest_y - fdf->map.smallest_y) / 2))
	// 	move_y += 3;
	// i = 0;
	// while (i < fdf->map.height)
	// {
	// 	j = 0;
	// 	while (j < fdf->map.width)
	// 	{
	// 		fdf->map.points[i][j].x += move_x;
	// 		fdf->map.points[i][j].y += move_y;
	// 		update_max_min_x_y(&(fdf->map.points[i][j]), &(fdf->map));
	// 		j++;
	// 	}
	// 	i++;
	// }

	//chatgpt way

	int x_center = (fdf->map.smallest_x + fdf->map.biggest_x) / 2;
    int y_center = (fdf->map.smallest_y + fdf->map.biggest_y) / 2;
    
    int x_screen_center = fdf->win_width / 2;
    int y_screen_center = fdf->win_height / 2;
    
    int delta_x = x_screen_center - x_center;
    int delta_y = y_screen_center - y_center;

	int i = 0;
	printf("delta_x %i, delta_y %i\n", delta_x, delta_y);
	while (i < fdf->map.height)
	{
		int j = 0;
		while (j < fdf->map.width)
		{
			fdf->map.points[i][j].x += delta_x;
			fdf->map.points[i][j].y += delta_y;
			update_max_min_x_y(&(fdf->map.points[i][j]), &(fdf->map));
			j++;
		}
		i++;
	}
}

void	error(void)
{
	puts(mlx_strerror(mlx_errno));
	exit(EXIT_FAILURE);
}

void	add_hooks(mlx_t *mlx, t_fdf *fdf)
{
	mlx_key_hook(mlx, &fdf_keyhook, fdf);
}

void	set_offsets(t_fdf *fdf)
{
	
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
			//extract this to its own function that is also used by zoom hook?
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
	fdf.map = map;
	init_map(&(fdf.map), argv[1]);
	isometric_transformation(&(fdf.map));
	init_view(&fdf);
	center_map(&(fdf));
	draw_map(&fdf);
	add_hooks(mlx, &fdf);
	if (mlx_image_to_window(mlx, fdf.img, 0, 0) < 0)
        error();
	mlx_loop(mlx);

	//TODO
	// Optional, terminate will clean up any leftovers, this is just to demonstrate.
	mlx_delete_image(mlx, fdf.img);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}
