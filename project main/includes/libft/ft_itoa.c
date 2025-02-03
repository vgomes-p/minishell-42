/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgomes-p <vgomes-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 12:54:15 by vgomes-p          #+#    #+#             */
/*   Updated: 2024/11/07 12:54:15 by vgomes-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_intlen(long int num)
{
	int	cnt;

	cnt = 0;
	if (num <= 0)
	{
		cnt++;
		num = -num;
	}
	while (num > 0)
	{
		cnt++;
		num /= 10;
	}
	return (cnt);
}

char	*ft_itoa(int num)
{
	long int	absnum;
	int			numlen;
	char		*str;

	absnum = num;
	numlen = ft_intlen(absnum);
	str = ft_calloc(numlen + 1, sizeof(char));
	if (!str)
		return (NULL);
	if (absnum < 0)
		absnum = -absnum;
	while (numlen > 0)
	{
		str[--numlen] = absnum % 10 + '0';
		absnum /= 10;
	}
	if (num < 0)
		str[0] = '-';
	return (str);
}
