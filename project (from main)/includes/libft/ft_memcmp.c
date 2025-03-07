/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgomes-p <vgomes-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 12:54:27 by vgomes-p          #+#    #+#             */
/*   Updated: 2024/11/07 12:54:27 by vgomes-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *str0, const void *str1, size_t numby)
{
	long int	cnt;

	cnt = -1;
	if (numby == 0)
		return (0);
	while (++cnt < (long int)numby)
		if (*(unsigned char *)(str0 + cnt) != *(unsigned char *)(str1 + cnt))
			return (*(unsigned char *)(str0 + cnt) -
			*(unsigned char *)(str1 + cnt));
	return (0);
}
