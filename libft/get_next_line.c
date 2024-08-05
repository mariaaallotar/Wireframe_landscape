/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maheleni <maheleni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 09:00:03 by maheleni          #+#    #+#             */
/*   Updated: 2024/05/23 09:00:05 by maheleni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*free_mallocs(char **line, char **rest_ptr)
{
	if (line != NULL && *line != NULL)
	{
		free(*line);
		*line = NULL;
	}
	if (rest_ptr != NULL && *rest_ptr != NULL)
	{
		free(*rest_ptr);
		*rest_ptr = NULL;
	}
	return (NULL);
}

static char	*create_line_and_set_rest(char **rest_ptr)
{
	char	*line;
	char	*new_rest;
	int		line_end_i;

	line_end_i = findchr(*rest_ptr, '\n');
	if (line_end_i == -1)
	{
		line_end_i = findchr(*rest_ptr, '\0');
		line = mod_substr(*rest_ptr, 0, '\0');
	}
	else
		line = mod_substr(*rest_ptr, 0, '\n');
	if (line == NULL)
		return (free_mallocs(NULL, rest_ptr));
	new_rest = mod_substr(*rest_ptr, (line_end_i + 1), '\0');
	if (new_rest == NULL)
		return (free_mallocs(&line, rest_ptr));
	free_mallocs(NULL, rest_ptr);
	*rest_ptr = new_rest;
	return (line);
}

static char	*join_rest_read(char *read_buf, char **rest_ptr, ssize_t read_len)
{
	char		*new_rest;
	size_t		rest_len;
	int			new_rest_len;

	rest_len = ft_strlen(*rest_ptr);
	new_rest_len = rest_len + read_len + 1;
	new_rest = (char *) malloc(new_rest_len * sizeof (char));
	if (new_rest == NULL)
		return (free_mallocs(NULL, rest_ptr));
	ft_memset(new_rest, '\0', new_rest_len);
	ft_strlcat(new_rest, *rest_ptr, new_rest_len);
	ft_strlcat(new_rest, read_buf, new_rest_len);
	free_mallocs(NULL, rest_ptr);
	ft_memset(read_buf, '\0', (BUFFER_SIZE + 1));
	return (new_rest);
}

static char	*read_next_line(int fd, char *read_buf, char **rest_ptr)
{
	ssize_t	bytes_read;
	char	*line;

	bytes_read = 1;
	while (findchr(*rest_ptr, '\n') == -1 && bytes_read != 0)
	{
		bytes_read = read(fd, read_buf, BUFFER_SIZE);
		if (bytes_read == -1)
			return (free_mallocs(NULL, rest_ptr));
		if (bytes_read == 0 && **rest_ptr == '\0')
			return (free_mallocs(NULL, rest_ptr));
		read_buf[bytes_read] = '\0';
		if (bytes_read != 0)
			*rest_ptr = join_rest_read(read_buf, rest_ptr, bytes_read);
		if (*rest_ptr == NULL)
			return (NULL);
	}
	line = create_line_and_set_rest(rest_ptr);
	if (line == NULL)
		return (free_mallocs(NULL, rest_ptr));
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*rest;
	char		read_buf[BUFFER_SIZE + 1];

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!rest)
	{
		rest = (char *) malloc(1 * sizeof(char));
		if (rest == NULL)
			return (NULL);
		ft_memset(rest, '\0', 1);
	}
	return (read_next_line(fd, read_buf, &rest));
}
