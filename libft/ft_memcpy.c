/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maheleni <maheleni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 14:27:50 by maheleni          #+#    #+#             */
/*   Updated: 2024/04/22 14:27:52 by maheleni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
* Copies n bytes from memory area src to memory area dst.
* If dst and src overlap, behavior is undefined.
* Parameters: 
	*dst - the destination to copy bytes to
	*src - the source to copy from
	n - amount of bytes to cpy
* Returns: 
	The destination
*/
void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	void	*orig_dst;

	orig_dst = dst;
	if (src == NULL && dst == NULL)
		return (NULL);
	while (n > 0)
	{
		*(char *)dst = *(char *)src;
		dst++;
		src++;
		n--;
	}
	return (orig_dst);
}
