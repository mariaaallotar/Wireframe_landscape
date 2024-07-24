/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maheleni <maheleni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 09:43:42 by maheleni          #+#    #+#             */
/*   Updated: 2024/04/30 09:43:43 by maheleni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
* Compares the first n bytes (each interpreted as unsigned char) of the memory
*	areas s1 and s2
* Parameters:
*	*s1 - first memory area to compare
*	*s2 - second memory area to compare
*	n - amount of bytes to compare
* Returns:
*	An integer that represents the difference in the first unequal bytes 
*		in the memory
*	(int > 0) - s1 is grater than s2
*	(int = 0) - s1 is equal to s2
*	(int < 0) - s1 is smaller than s2
*/
int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	if (n == 0)
		return (0);
	while ((unsigned char) *(char *) s1
		== (unsigned char) *(char *) s2)
	{
		s1++;
		s2++;
		n--;
		if (n == 0)
			return (0);
	}
	return ((unsigned char) *(char *) s1 - (unsigned char) *(char *) s2);
}
