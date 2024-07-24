/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_num.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maheleni <maheleni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 10:42:37 by maheleni          #+#    #+#             */
/*   Updated: 2024/06/02 10:42:39 by maheleni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	rec_print_num(long nb, int written)
{
	char	c;
	int		write_ret;

	if (nb >= 10)
	{
		written = rec_print_num(nb / 10, written);
		if (written < 0)
			return (-1);
	}
	c = (nb % 10) + '0';
	write_ret = write(1, &c, 1);
	if (write_ret < 0)
		return (-1);
	written++;
	return (written);
}

int	print_num(va_list list)
{
	long	n;
	int		write_ret;

	n = (long) va_arg(list, int);
	write_ret = 0;
	if (n < 0)
	{
		write_ret = write(1, "-", 1);
		if (write_ret < 0)
			return (-1);
		n = n * -1;
	}
	write_ret += rec_print_num(n, 0);
	if (write_ret < 0)
		return (-1);
	return (write_ret);
}

int	print_unsigned(va_list list)
{
	unsigned int	n;
	int				write_ret;

	n = va_arg(list, unsigned int);
	write_ret = 0;
	write_ret = rec_print_num(n, write_ret);
	return (write_ret);
}
