/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maheleni <maheleni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 11:24:54 by maheleni          #+#    #+#             */
/*   Updated: 2024/04/25 11:25:10 by maheleni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
* Locates the first occurrence of c (converted to an unsigned char) in s.
* Continues searching even after '\0' if there is still n left.
* Parameters:
*	*s - pointer to memory to search from
*	c - int representation of character to find
*	n - amount of memorylocations to search
* Returns:
*	Location (void pinter) of first occurrance where c was found
*	NULL if c was NOT found anywhere
*/
void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	c_n_str;

	while (n > 0)
	{
		c_n_str = (unsigned char) *(char *) s;
		if (c_n_str == (unsigned char) c)
			return ((void *) s);
		s++;
		n--;
	}
	return (NULL);
}
