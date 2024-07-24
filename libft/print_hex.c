/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_pointer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maheleni <maheleni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 10:41:08 by maheleni          #+#    #+#             */
/*   Updated: 2024/06/02 10:41:10 by maheleni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	write_string(const char *str)
{
	int	count;
	int	write_ret;

	count = 0;
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

static int	count_digits(uintptr_t n)
{
	int	count;

	count = 0;
	if (n == 0)
		return (1);
	while (n != 0)
	{
		n = n / 16;
		count++;
	}
	return (count);
}

int	print_pointer(va_list list)
{
	int			write_ret;
	uintptr_t	address;
	int			digits;
	char		*a;

	write_ret = write(1, "0x", sizeof(char) * 2);
	if (write_ret == -1)
		return (-1);
	address = (uintptr_t) va_arg(list, void *);
	digits = count_digits(address);
	a = (char *) malloc ((digits + 1) * sizeof(char));
	if (a == NULL)
		return (-1);
	a[digits] = '\0';
	while (--digits >= 0)
	{
		if (address % 16 < 10)
			a[digits] = '0' + (address % 16);
		else
			a[digits] = 'a' + (address % 16) - 10;
		address /= 16;
	}
	write_ret += write_string(a);
	free(a);
	return (write_ret);
}

int	print_hex(va_list list, char type)
{
	int				write_ret;
	unsigned int	num;
	int				digits;
	char			*a;

	num = va_arg(list, unsigned int);
	digits = count_digits(num);
	a = (char *) malloc ((digits + 1) * sizeof(char));
	if (a == NULL)
		return (-1);
	a[digits] = '\0';
	while (--digits >= 0)
	{
		if (num % 16 < 10)
			a[digits] = '0' + (num % 16);
		else if (type == 'x')
			a[digits] = 'a' + (num % 16) - 10;
		else
			a[digits] = 'A' + (num % 16) - 10;
		num /= 16;
	}
	write_ret = write_string(a);
	free(a);
	return (write_ret);
}
