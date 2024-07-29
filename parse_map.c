/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maheleni <maheleni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 09:45:46 by maheleni          #+#    #+#             */
/*   Updated: 2024/07/29 13:07:52 by maheleni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	set_point(t_map *map, int x, int y, int z)
{
	t_point	point;

	//DEBUG
	float new_x = x;
	float new_y = y;

	point.x = x;
	point.y = y;
	point.z = z;
	point.height = z;
	map->points[y-1][x-1] = point;
}

static char*	skip_to_next_word(char *line)
{
	while (*line != ' ')
	{
		if (*line == '\0')
			return (line);
		line++;
	}
	line++;
	return (line);
}

static void	populate_map(int i, char *line, t_map *map)
{
	int	j;

	map->points[i-1] = malloc (map->width * sizeof (t_point));
	if (map->points[i-1] == NULL)
	{
		//free_points();
		error();
	}
	j = 1;
	while (*line != '\0')
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
			if (errno != 0)
			{
				free(map->points);
				error();
			}
			return ;
		}
		populate_map(i, line, map);
		free(line);
		i++;
	}
	return ;
}

void	get_dimensions(int fd, t_map *map)
{
	char	*line;
	int		height;

	height = 0;
	line = get_next_line(fd);
	if (line == NULL)
	{
		printf("In get_dimensions error\n");
		error();
	}
	height++;
	map->width = ft_count_words(line);
	while (get_next_line(fd) != NULL)
		height++;
	map->height = height;
}
