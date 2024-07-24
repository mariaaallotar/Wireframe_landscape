/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maheleni <maheleni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 09:46:21 by maheleni          #+#    #+#             */
/*   Updated: 2024/04/30 09:46:22 by maheleni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
* Converts the initial portion of the string pointed to by str to
*	int representation.
* Parameters:
*	*str - string of numbers to convert to int
* Returns:
*	The number in int representation
* Note:
*	When INT overflows or underflows the function keeps returning numbers, 
*		when LONG overflows the function returns -1 and when LONG underflows
*		the function returns 0
*/
int	ft_atoi(const char *str)
{
	int		sign;
	long	res;
	long	prev;

	sign = 1;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-')
		sign = -1;
	if (*str == '+' || *str == '-')
		str++;
	res = 0;
	while (*str >= '0' && *str <= '9')
	{
		prev = res;
		res = res * 10 + (*str - '0');
		if (prev != res / 10 && sign == -1)
			return (0);
		if (prev != res / 10 && sign == 1)
			return (-1);
		str++;
	}
	return ((int)(res * sign));
}
