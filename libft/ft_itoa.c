/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maheleni <maheleni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 15:58:42 by maheleni          #+#    #+#             */
/*   Updated: 2024/04/30 15:58:44 by maheleni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
* Counts how many digits are in the number n
* Parameters:
*	n - number to count digits of
*/
static int	count_digits(long n)
{
	int	count;

	count = 0;
	if (n == 0)
		return (1);
	while (n != 0)
	{
		n = n / 10;
		count++;
	}
	return (count);
}

/**
* Converts an integer to ascii into the string given
* Parameters:
*	num - number to convert
*	*str - string to put the number into
*	i - last index of string
*/
static void	convert_integer(long num, char *str, int i)
{
	while (i-- > 0)
	{
		str[i] = (num % 10) + '0';
		num = num / 10;
	}
}

/**
* Allocates and returns a string representing the integer received as an
* argument
* Parameters:
*	n - int number
* Returns:
*	A string of that number
*/
char	*ft_itoa(int n)
{
	int		is_neg;
	int		digits;
	char	*a;
	int		i;
	long	num;

	num = (long) n;
	is_neg = 0;
	if (num < 0)
	{
		is_neg = 1;
		num = -num;
	}
	digits = count_digits(num);
	i = digits + is_neg;
	a = (char *)malloc(sizeof(char) * (i + 1));
	if (a == NULL)
		return (NULL);
	a[i] = '\0';
	convert_integer(num, a, i);
	if (is_neg)
		a[0] = '-';
	return (a);
}
