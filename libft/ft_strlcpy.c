/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maheleni <maheleni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 12:25:23 by maheleni          #+#    #+#             */
/*   Updated: 2024/04/23 12:25:36 by maheleni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
* Copies up to (dstsize - 1) characters from the string src to dst,
* 	NUL-terminating the result if dstsize is not 0.
* If the src and dst strings overlap, the behavior is undefined.
* Parameters:
*	*dst - the destination to copy to
*	*src - the source to copy from
*	dstsize - the size of dst memory
* Returns:
*	The size of the string it tried to copy, in practice the size of src
*/
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	src_len;
	size_t	i;

	src_len = ft_strlen(src);
	if (dstsize > 0)
	{
		i = 0;
		while (i < src_len && i < (dstsize - 1))
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	return (src_len);
}
