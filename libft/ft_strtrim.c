/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maheleni <maheleni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 12:47:11 by maheleni          #+#    #+#             */
/*   Updated: 2024/04/30 12:47:13 by maheleni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
* Allocates and returns a copy of string 's' with the characters specified in
* 'set' removed from the beginning and the end of the string
* Example:					Example:
*	string - cbahahab			string - cbahah
*	set - abc					set - abc
*	returns: hah				returns: hah
* Parameters:
*	*s - string to be trimmed
*	*set - a set of characters to trim from 's'
* Returns;
*	The trimmed string
*	NULL if the allocation fails
*/
char	*ft_strtrim(char const *s, char const *set)
{
	size_t	start_i;
	size_t	end_i;

	start_i = 0;
	end_i = ft_strlen(s);
	if (!*s)
		return (ft_strdup(""));
	if (!*set)
		return (ft_strdup(s));
	while (ft_strchr(set, s[start_i]))
		start_i++;
	while (ft_strrchr(set, s[end_i]))
		end_i--;
	return (ft_substr(s, start_i, end_i - start_i + 1));
}
