/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maheleni <maheleni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 11:35:51 by maheleni          #+#    #+#             */
/*   Updated: 2024/04/30 11:35:53 by maheleni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
* Allocates and returns a new string, which is the result of the concatenation
*	of 's1' and 's2'
* Parameters:
*	*s1 - the prefix string
*	*s2 - the suffix string
* Returns:
*	The string
*	NULL if allocation failed
*/
char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*join;
	size_t	s1_len;
	size_t	s2_len;

	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	join = (char *) malloc((s1_len + s2_len + 1) * sizeof (char));
	if (join == NULL)
		return (NULL);
	ft_strlcpy(join, s1, s1_len + 1);
	ft_strlcat(join, s2, (s1_len + s2_len + 1));
	return (join);
}
