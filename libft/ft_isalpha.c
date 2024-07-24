/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maheleni <maheleni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 09:27:31 by maheleni          #+#    #+#             */
/*   Updated: 2024/04/19 09:27:33 by maheleni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
* Determines if a character is a letter (alphabetic character)
* Works only on characters in the standard ascii table (dec 0-127)
* Parameters: 
	c - int representation of a character
* Returns: 
	1 - if c is a letter
	0 - otherwise
*/
int	ft_isalpha(int c)
{
	if (ft_islower(c) || ft_isupper(c))
		return (1);
	return (0);
}
