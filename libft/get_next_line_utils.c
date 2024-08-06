/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maheleni <maheleni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 10:44:27 by maheleni          #+#    #+#             */
/*   Updated: 2024/08/06 10:21:34 by maheleni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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
