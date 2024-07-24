/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maheleni <maheleni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 10:16:11 by maheleni          #+#    #+#             */
/*   Updated: 2024/04/24 10:16:13 by maheleni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
* Appends (concatenate) string src to the end of dst
*	It will append at most dstsize - strlen(dst) - 1 characters.  
*	It will then NUL-terminate, unless dstsize is 0 or the original dst string
*	was longer than dstsize
* If the src and dst strings overlap, the behavior is undefined.
* Parameters:
*	*dst - the destination to append to
*	*src - the source to copy from
*	dstsize - the size of dst memory
* Returns:
*	The size of the string it tried to create, in practice the initial length
*		of dst plus the length of src
*/
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
