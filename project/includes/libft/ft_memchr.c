/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgomes-p <vgomes-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 12:54:20 by vgomes-p          #+#    #+#             */
/*   Updated: 2024/11/07 12:54:20 by vgomes-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *str, int ch, size_t numby)
{
	if (numby == '\0')
		return (NULL);
	while (numby--)
	{
		if (*(char *)str == (char)ch)
			return ((char *)str);
		str++;
	}
	return (NULL);
}
