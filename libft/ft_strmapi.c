/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maheleni <maheleni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 10:11:08 by maheleni          #+#    #+#             */
/*   Updated: 2024/05/03 10:11:10 by maheleni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
* Applies the function ’f’ to each character of the string ’s’ to create a new
*	string resulting from successive applications of ’f’
* Parameters:
*	*s - string to apply f to
*	f - a function to apply to every character in string s
*		Parameters:
*			unsigned int - index of the char in s
*			char - the character to apply the function to
*		Returns:
*			a character
* Returns:
*	The string created from the successive applications of ’f’
*	New empty string if s is empty
*	NULL if the allocation fails
*/
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*new_s;
	unsigned int	i;

	if (s == NULL)
		return (ft_strdup(""));
	new_s = (char *) malloc((ft_strlen(s) + 1) * sizeof(char));
	if (new_s == NULL)
		return (NULL);
	i = 0;
	while (s[i] != '\0')
	{
		new_s[i] = f(i, s[i]);
		i++;
	}
	new_s[i] = '\0';
	return (new_s);
}
