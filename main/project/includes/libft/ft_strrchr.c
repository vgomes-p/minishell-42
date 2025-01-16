/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgomes-p <vgomes-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 12:56:37 by vgomes-p          #+#    #+#             */
/*   Updated: 2024/11/07 12:56:37 by vgomes-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int ch)
{
	int	cnt;

	cnt = ft_strlen(str);
	while (cnt != 0 && str[cnt] != (char)ch)
		cnt--;
	if (str[cnt] == (char)ch)
		return ((char *)str + cnt);
	return (NULL);
}
