/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgomes-p <vgomes-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 12:54:56 by vgomes-p          #+#    #+#             */
/*   Updated: 2024/11/07 12:54:56 by vgomes-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int num, int fd)
{
	long int	nwnum;

	nwnum = num;
	if (nwnum < 0)
	{
		nwnum *= -1;
		ft_putchar_fd('-', fd);
	}
	if (nwnum > 9)
		ft_putnbr_fd(nwnum / 10, fd);
	ft_putchar_fd(nwnum % 10 + '0', fd);
}
