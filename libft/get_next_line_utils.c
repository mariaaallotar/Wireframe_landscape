/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maheleni <maheleni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 10:44:27 by maheleni          #+#    #+#             */
/*   Updated: 2024/05/23 10:44:29 by maheleni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*mod_substr(char *str, int start_i, char end_char)
{
	char	*sub;
	int		sub_end_i;
	int		sub_len;
	int		i;

	sub_end_i = findchr(str, end_char);
	if (end_char == '\n')
		sub_end_i++;
	sub_len = sub_end_i - start_i;
	if (sub_len < 0)
	{
		sub_len = 0;
		sub_end_i = -1;
	}
	sub = (char *) malloc((sub_len + 1) * sizeof(char));
	if (sub == NULL)
		return (NULL);
	i = -1;
	while (start_i < sub_end_i)
	{
		sub[++i] = str[start_i];
		start_i++;
	}
	sub[sub_len] = '\0';
	return (sub);
}

int	findchr(char *str, char c)
{
	int	i;

	if (str == NULL)
		return (-1);
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	if (str[i] == c)
		return (i);
	return (-1);
}

void	*ft_memset(void *s, int c, size_t len)
{
	unsigned char	*str;

	str = (unsigned char *) s;
	while (len > 0)
	{
		*str = (unsigned char) c;
		str++;
		len--;
	}
	return (s);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (*s != '\0')
	{
		i++;
		s++;
	}
	return (i);
}

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	dst_len;
	size_t	src_len;
	size_t	i;

	dst_len = ft_strlen(dst);
	src_len = ft_strlen(src);
	if (dstsize > dst_len && dstsize > 0)
	{
		i = 0;
		while (i < dstsize - dst_len - 1 && i < src_len)
		{
			dst[i + dst_len] = src[i];
			i++;
		}
		dst[i + dst_len] = '\0';
	}
	if (dst_len >= dstsize)
		dst_len = dstsize;
	return (dst_len + src_len);
}
