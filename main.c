#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <memory.h>
#include <math.h>
#include "MLX42/MLX42.h"
#define WIDTH 520
#define HEIGHT 520

typedef struct s_point
{
	float	x;
	float	y;
	float	z;
}	t_point;

typedef struct s_map
{
	int 	height;
	int 	width;
	t_point	*points;
}	t_map;

void drawline(int x0, int y0, int x1, int y1, mlx_image_t* img)  
{  
	int dx, dy, p, x, y;

	dx = x1 - x0;
	dy = y1 - y0;
	p = 2 * dy - dx;
	x = x0;
	y = y0;
	while(x < x1)
	{
		if(p >= 0)
		{  
			mlx_put_pixel(img, x, y, 0xFF0000FF);
			y = y + 1;
			p = p + 2 * dy - 2 * dx;
		}
		else
		{
			mlx_put_pixel(img, x, y, 0xFF0000FF);
			p = p + 2 * dy;
		}
		x = x + 1;
	}
}  

t_point	isometric_transformation(int x, int y, int z)
{
	int	r1 = 3;
	int c1 = 3;
	int r2 = 3;
	int c2 = 1;

	float	m1[3][3] = { { sqrt(2)/2, -(sqrt(2)/2), 0 }, { sqrt(2)/2, sqrt(2)/2, 0 }, { 0, 0, 1 } };
	float	m2[3][3] = { {1, 0, 0}, {0, sqrt(3)/3, -(sqrt(6)/3)}, {0, sqrt(6)/3, sqrt(3)/3}};
	float	result[3][1];

	// printf("ISOMETRIC:\n");
	int i = 0;
	while (i < 3)
	{
		result[i][0] = x * m1[i][0] + y * m1[i][1] + z * m1[i][2];
		i++;
	}

	float new_x = result[0][0];
	float new_y = result[1][0];
	float new_z = result[2][0];

	i = 0;
	while (i < 3)
	{
		result[i][0] = new_x * m2[i][0] + new_y * m2[i][1] + new_z * m2[i][2];
		i++;
	}

	t_point transformed_point;
	transformed_point.x = result[0][0];
	transformed_point.y = result[1][0];
	transformed_point.z = result[2][0];

	// printf("Returning\n");
    return (transformed_point);
}

t_point orthographic_projection(t_point point)
{
	float	result[3][1];
	int m1[3][3] = { { 1, 0, 0 }, { 0, 1, 0 }, { 0, 0, 0 } };

	printf("ORTOGRAPHIC:\n");
	int i = 0;
	while (i < 3)
	{
		result[i][0] = (point.x * m1[i][0] + point.y * m1[i][1] + point.z * m1[i][2]);
		printf("%f\n", result[i][0]);
		i++;
	}
	point.x = result[0][0];
	point.y = result[1][0];
	point.z = result[2][0];
	return (point);
}

void	get_dimensions(int fd, t_map *map)
{
	char	*line;
	int		height;

	height = 0;
	line = get_next_line(fd);
	if (line == NULL)
		error;
	height++;
	map->width = count_words(line);		//TODO
	while (get_next_line(fd) != NULL)
		height++;
	map->height = height;
}

void	parse_map(int fd, t_map *map)
{
	char	*line;
	t_point	point;
	int		*heights;
	int		i;
	int		j;

	i = 0;
	heights = malloc (map->width * sizeof(int));
	if (heights == NULL)
		error();
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
		{
			free(heights);
			return ;
		}
		heights = get_heights(line);
		j = 0;
		while (j < map->width)
		{
			point.x = j;
			point.y = i;
			point.z = *heights++;
			*(map->points) = point;
			(map->points)++;
			heights++;
			j++;
		}
		i++;
	}
}

t_map	read_map(int fd)
{
	t_map	map;

	get_dimensions(fd, &map);
	parse_map(fd, &map);
	return (map);
}

static void error(void)
{
	puts(mlx_strerror(mlx_errno));
	exit(EXIT_FAILURE);
}

int32_t	main(void)
{
	t_map map;
	int half_screen_width = WIDTH / 2;
  	int half_screen_height = HEIGHT / 2;
	uint32_t x_screen;
	u_int32_t y_screen;

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

	// mlx_put_pixel(img, 100, 100, 0xFF0000FF); //red
	// mlx_put_pixel(img, 100, 200, 0x00FF00FF); //green
	// mlx_put_pixel(img, 200, 100, 0x0000FFFF); //blue
	// mlx_put_pixel(img, 200, 200, 0xFFFFFF00); //black

	int i = 1;
	while (i <= 3)
	{
		int j = 1;
		while (j <= 3)
		{
			if (i == 2 && j == 2)
			{
				map.points[i][j] = orthographic_projection(isometric_transformation(i * 10, j * 10, 5));
				mlx_put_pixel(img, (map.points[i][j].x) + half_screen_width, (map.points[i][j].y) + half_screen_height, 0x00FF00FF);
			}
			else
			{
				map.points[i][j] = orthographic_projection(isometric_transformation(i * 10, j * 10, 0));
				mlx_put_pixel(img, (map.points[i][j].x) + half_screen_width, (map.points[i][j].y) + half_screen_height, 0xFF0000FF);
			}
			j++;
		}
		i++;
	}
	drawline(50, 50, 51, 100, img);

	// map.points[0][0] = orthographic_projection(isometric_transformation(20, 20, 0));
	// mlx_put_pixel(img, map.points[0][0].x, map.points[0][0].y, 0xFF0000FF);
	// printf("Pixel put to X: %f and Y: %f\n", map.points[0][0].x, map.points[0][0].y);

	// map.points[0][1] = orthographic_projection(isometric_transformation(20, 40, 0));
	// mlx_put_pixel(img, map.points[0][1].x, map.points[0][1].y, 0x00FF00FF);
	// printf("Pixel put to X: %f and Y: %f\n", map.points[0][1].x, map.points[0][1].y);

	// map.points[1][0] = orthographic_projection(isometric_transformation(40, 20, 0));
	// mlx_put_pixel(img, map.points[1][0].x, map.points[1][0].y, 0x0000FFFF);
	// printf("Pixel put to X: %f and Y: %f\n", map.points[1][0].x, map.points[1][0].y);

	// map.points[1][1] = orthographic_projection(isometric_transformation(40, 40, 0));
	// mlx_put_pixel(img, map.points[1][1].x, map.points[1][1].y, 0x000000FF);
	// printf("Pixel put to X: %f and Y: %f\n", map.points[1][1].x, map.points[1][1].y);

	// Display an instance of the image
	if (mlx_image_to_window(mlx, img, 0, 0) < 0)
        error();

	mlx_loop(mlx);

	// Optional, terminate will clean up any leftovers, this is just to demonstrate.
	mlx_delete_image(mlx, img);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}