/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maheleni <maheleni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 10:08:46 by maheleni          #+#    #+#             */
/*   Updated: 2024/05/03 10:08:47 by maheleni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
* Outputs the integer ’n’ to the given file descriptor
* Parameters:
*	n - number to output
*	fd - filedescriptor on which to write
*/
void	ft_putnbr_fd(int n, int fd)
{
	char	digit;
	long	num;

	num = (long)n;
	if (n == 0)
	{
		write(fd, "0", 1);
		return ;
	}
	if (num < 0)
	{
		write(fd, "-", 1);
		num = -num;
	}
	if (n / 10)
		ft_putnbr_fd(num / 10, fd);
	digit = '0' + (num % 10);
	write(fd, &digit, 1);
}
