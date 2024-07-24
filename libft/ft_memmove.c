/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maheleni <maheleni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 09:02:05 by maheleni          #+#    #+#             */
/*   Updated: 2024/04/23 09:02:07 by maheleni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
* Copies n bytes from memory area src to memory area dst
* Works even if src and dst overlap (the function is bidirectional).
* Parameters: 
	*dst - the destination to copy bytes to
	*src - the source to copy from
	n - amount of bytes to cpy
* Returns: 
	The destination
*/
void	*ft_memmove(void *dst, const void *src, size_t n)
{
	int	i;

	if (dst == NULL && src == NULL)
		return (NULL);
	if (src < dst)
	{
		i = (int)n - 1;
		while (i >= 0)
		{
			*(char *)(dst + i) = *(char *)(src + i);
			i--;
		}
	}
	else
	{
		i = 0;
		while (i < (int)n)
		{
			*(char *)(dst + i) = *(char *)(src + i);
			i++;
		}
	}
	return (dst);
}
