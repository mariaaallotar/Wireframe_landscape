/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maheleni <maheleni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 09:45:46 by maheleni          #+#    #+#             */
/*   Updated: 2024/08/12 12:09:26 by maheleni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	set_point(t_map *map, int x, int y, int z)
{
	t_point	point;

	point.x = x;
	point.y = y;
	point.z = z;
	update_max_min_x_y(&point, map);
	point.right_edge = 0;
	if (x == map->width)
		point.right_edge = 1;
	point.bottom_edge = 0;
	if (y == map->height)
		point.bottom_edge = 1;
	map->points[y-1][x-1] = point;
}

static char*	skip_to_next_word(char *line)
{
	while (*line != '\0' && *line != ' ')
		line++;
	if (*line == '\0')
		return (line);
	while (*line != '\0' && *line == ' ')
		line++;
	return (line);
}

void	free_points(int row_index, t_map *map)
{
	while (row_index >= 0)
	{
		if (map->points[row_index] == NULL)
		{
			row_index--;
			continue ;
		}
		if (&(map->points[row_index][0]) != NULL)
			free(&(map->points[row_index][0]));

		row_index--;
	}
	free(map->points);
}

static void	populate_map(int i, char *line, t_map *map)
{
	int	j;

	map->points[i-1] = malloc (map->width * sizeof (t_point));
	if (map->points[i-1] == NULL)
	{
		free(line);
		free_points(i - 1, map);
		error();
	}
	j = 1;
	while (j <= map->width)
	{
		set_point(map, j, i, ft_atoi(line));
		line = skip_to_next_word(line);
		j++;
	}
}

void	parse_map(int fd, t_map *map)
{
	char	*line;
	int		i;

	i = 1;
	while (i <= map->height)
	{
		line = get_next_line(fd);
		if (line == NULL)
		{
			free_points(i - 1, map);
			error();
		}
		populate_map(i, line, map);
		free(line);
		i++;
	}
	return ;
}

static int	count_substrings(const char *s, char c)
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

void	get_dimensions(int fd, t_map *map)
{
	char	*line;
	int		height;

	height = 0;
	line = get_next_line(fd);
	if (line == NULL)
	{
		error();
	}
	height++;
	map->width = count_substrings(line, ' ');
	free(line);
	line = get_next_line(fd);
	while (line != NULL)
	{
		height++;
		free(line);
		line = get_next_line(fd);
	}
	map->height = height;
}
