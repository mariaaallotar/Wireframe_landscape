/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_string.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maheleni <maheleni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 10:39:48 by maheleni          #+#    #+#             */
/*   Updated: 2024/06/02 10:39:50 by maheleni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	print_string(va_list list)
{
	char	*str;
	int		count;
	int		write_ret;

	str = va_arg(list, char *);
	count = 0;
	if (str == NULL)
		return (write(1, "(null)", 6 * sizeof(char)));
	while (*str != '\0')
	{
		write_ret = write(1, str, sizeof(char));
		if (write_ret < 0)
			return (-1);
		count++;
		str++;
	}
	return (count);
}

int	print_char(va_list list)
{
	char	c;

	c = va_arg(list, int);
	return (write(1, &c, sizeof(char)));
}
