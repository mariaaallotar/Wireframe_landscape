/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maheleni <maheleni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 09:47:03 by maheleni          #+#    #+#             */
/*   Updated: 2024/07/28 11:01:09 by maheleni         ###   ########.fr       */
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
	float	zoom;
	t_point	**points;
}	t_map;

void	get_dimensions(int fd, t_map *map);
void	parse_map(int fd, t_map *map);
void	isometric_transformation(t_point *point);
void	rotate_arund_z(int deg, t_point *point);
void	set_zoom_factor(t_map *map);
void	error(void);


#endif