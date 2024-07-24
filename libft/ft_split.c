/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maheleni <maheleni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 14:09:33 by maheleni          #+#    #+#             */
/*   Updated: 2024/04/30 14:09:47 by maheleni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
* Counts the amount of substrings in the string 's'
* Parameters:
*	*s - string the substrings are located in
*	c - delimiter character
* Returns:
*	How many substrings are in the substring
*/
static int	count_substrings(const char *s, char c)
{
	int	count;
	int	in_substring;

	count = 0;
	in_substring = 0;
	while (*s)
	{
		if (*s != c && !in_substring)
		{
			in_substring = 1;
			count++;
		}
		else if (*s == c)
			in_substring = 0;
		s++;
	}
	return (count);
}

/**
* Counts the length of a substring
* Parameters:
*	*s - string the substring is located in
*	c - delimiter character
* Returns:
*	How many characters is in the substring
*/
static int	sub_length(char const *s, char c)
{
	int	len;

	len = 0;
	while (*s != c && *s != '\0')
	{
		len++;
		s++;
	}
	return (len);
}

static void	*free_everything(char **mem, int i)
{
	while (i >= 0)
	{
		free(mem[i]);
		i--;
	}
	free(mem);
	return (NULL);
}

/**
* Allocates and returns an array of strings obtained by splitting 's' using
*	the character 'c' as a delimiter. The array must end with a NULL pointer
* Parameters:
*	*s - string to be split
*	c - delimiter character
* Returns:
*	Array of new strings resulting from the split
*	NULL if the allocation fails
*/
char	**ft_split(char const *s, char c)
{
	char		**strings;
	int			sub_len;
	int			i;

	strings = (char **) malloc((count_substrings(s, c) + 1) * sizeof(char *));
	if (strings == NULL)
		return (NULL);
	i = 0;
	while (*s != '\0')
	{
		if (*s == c)
		{
			s++;
			continue ;
		}
		sub_len = sub_length(s, c);
		strings[i] = ft_substr(s, 0, sub_len);
		if (strings[i] == NULL)
			return (free_everything(strings, i));
		s = s + sub_len;
		i++;
	}
	strings[i] = NULL;
	return (strings);
}
