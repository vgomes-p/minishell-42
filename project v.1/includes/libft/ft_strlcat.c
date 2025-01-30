/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgomes-p <vgomes-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 12:56:02 by vgomes-p          #+#    #+#             */
/*   Updated: 2024/11/07 12:56:02 by vgomes-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t destsz)
{
	size_t	lenx;
	size_t	len0;
	size_t	len1;

	lenx = 0;
	len0 = ft_strlen(dest);
	len1 = ft_strlen(src);
	if (destsz <= len0)
		return (len1 + destsz);
	while (src[lenx] && (len0 + 1) < destsz)
		dest[len0++] = src[lenx++];
	dest[len0] = '\0';
	return (ft_strlen(dest) + ft_strlen(&src[lenx]));
}
