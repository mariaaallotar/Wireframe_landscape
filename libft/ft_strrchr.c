/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maheleni <maheleni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 12:22:48 by maheleni          #+#    #+#             */
/*   Updated: 2024/04/24 12:22:50 by maheleni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
* Locates the last occurrence of c (converted to a char) in the string 
*	pointed to by s.
* The terminating null character is considered to be part of the 
*	string; therefore if c is `\0', the functions locate the terminating `\0'.
* Parameters:
*	*s - pointer to the string to find character c from
*	c - int representation of the character to find
* Returns:
*	Pointer to the last occurance of the character found.
*	NULL if c is not found anywhere in the string
*/
char	*ft_strrchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (*s != '\0')
	{
		s++;
		i++;
	}
	if ((char) c == '\0')
		return ((char *) s);
	while (i >= 0)
	{
		if (*s == (char) c)
			return ((char *) s);
		s--;
		i--;
	}
	return (NULL);
}
