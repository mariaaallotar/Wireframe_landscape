/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maheleni <maheleni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 11:10:58 by maheleni          #+#    #+#             */
/*   Updated: 2024/04/22 11:10:59 by maheleni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
* Writes len bytes of value c (converted to an unsigned char) to the string s
* Parameters: 
	*s - string to write into
	c - int representation of the character to write into the string
	len - length of string to write the charcter into
* Returns: 
	The modified string as a void pointer
*/
void	*ft_memset(void *s, int c, size_t len)
{
	unsigned char	*str;

	str = (unsigned char *) s;
	while (len > 0)
	{
		*str = (unsigned char) c;
		str++;
		len--;
	}
	return (s);
}
