/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgomes-p <vgomes-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 12:56:51 by vgomes-p          #+#    #+#             */
/*   Updated: 2024/11/07 12:56:51 by vgomes-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *str, unsigned int start, size_t len)
{
	char	*nwstr;
	size_t	lenstr;

	if (!str)
		return (NULL);
	lenstr = ft_strlen(str);
	if (start >= lenstr)
		return (ft_strdup(""));
	if (lenstr - start >= len)
		nwstr = malloc((len + 1) * sizeof(char));
	else
		nwstr = malloc((lenstr - start + 1) * sizeof(char));
	if (nwstr)
	{
		if (len > lenstr + 1)
			len = lenstr + 1;
		ft_strlcpy(nwstr, (str + start), (len + 1));
	}
	else
		return (NULL);
	return (nwstr);
}
