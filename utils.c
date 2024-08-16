/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maheleni <maheleni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 13:19:43 by maheleni          #+#    #+#             */
/*   Updated: 2024/08/16 11:10:21 by maheleni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	validate_file(char *file)
{
	int	str_len;

	str_len = ft_strlen(file);
	file = file + str_len - 4;
	if (ft_strncmp(file, ".fdf", 4) == 0)
		return ;
	ft_printf("The name of a file must end in '.fdf'.\n");
	exit(EXIT_FAILURE);
}

int	count_substrings(const char *s, char c)
{
	int	count;
	int	in_substring;

	count = 0;
	in_substring = 0;
	while (*s && *s != '\n')
	{
		if (*s != c && !in_substring)
		{
			in_substring = 1;
			count++;
		}
		else if (*s == c)
			in_substring = 0;
		s++;
	}
	return (count);
}

void	update_max_min_x_y(t_point *point, t_map *map)
{
	if (point->x < map->smallest_x)
		map->smallest_x = point->x;
	if (point->x >= map->biggest_x)
		map->biggest_x = point->x;
	if (point->y < map->smallest_y)
		map->smallest_y = point->y;
	if (point->y >= map->biggest_y)
		map->biggest_y = point->y;
}
