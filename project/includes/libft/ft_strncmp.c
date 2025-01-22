/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgomes-p <vgomes-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 12:56:26 by vgomes-p          #+#    #+#             */
/*   Updated: 2024/11/07 12:56:26 by vgomes-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *str0, const char *str1, size_t numby)
{
	size_t	cnt;

	cnt = 0;
	if (numby == 0)
		return (0);
	while (str0[cnt] && (str0[cnt] == str1[cnt]) && cnt < (numby - 1))
		cnt++;
	return ((unsigned char)str0[cnt] - (unsigned char)str1[cnt]);
}
