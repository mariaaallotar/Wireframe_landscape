/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_count_words.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maheleni <maheleni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 10:59:37 by maheleni          #+#    #+#             */
/*   Updated: 2024/07/24 12:04:14 by maheleni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int ft_count_words(char *line)
{
    int i;
    int count;

    if (line == NULL)
        return (0);
    i = 0;
    count = 0;
    while (line[i] == ' ')
        i++;
    while (line[i] != '\0')
    {
        if (line[i] == ' ' || line[i + 1] == '\0')
        {
            count++;
            i++;
            while (line[i] == ' ')
                i++;
            if (line[i] == '\0')
                return (count);
        }
        else
            i++;
    }
    return (count);
}