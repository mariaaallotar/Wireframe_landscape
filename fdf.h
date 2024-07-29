/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maheleni <maheleni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 09:47:03 by maheleni          #+#    #+#             */
/*   Updated: 2024/07/29 14:39:04 by maheleni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <memory.h>
#include <math.h>
#include <fcntl.h>
#include <errno.h>
#include "MLX42/MLX42.h"
#include "libft/libft.h"

#define WIDTH 1800
#define HEIGHT 1200
#define M_PI 3.14159265358979323846

typedef struct s_point
{
	float	x;
	float	y;
	float	z;
	int		height;
}	t_point;

typedef struct s_view
{
	float	zoom;
	float	width_offset;
	float	height_offset;
	float	rotation;
}	t_view;

typedef struct s_map
{
	int 		height;
	int 		width;
	t_point		**points;
	t_view		view;
	mlx_image_t	*img;
}	t_map;


void	get_dimensions(int fd, t_map *map);
void	parse_map(int fd, t_map *map);
void	isometric_transformation(t_point *point);
void	rotate_around_z(float deg, t_point *point);
void	set_zoom_factor(t_view *view, t_map *map);
void    fdf_keyhook(mlx_key_data_t keydata, void* param);
void	draw(t_map *map);
void	error(void);


#endif