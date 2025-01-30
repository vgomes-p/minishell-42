/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgomes-p <vgomes-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 12:56:45 by vgomes-p          #+#    #+#             */
/*   Updated: 2024/11/07 12:56:45 by vgomes-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *str0, char const *set)
{
	char	*nwstr;
	size_t	cnt;

	if (!str0 || !set)
		return (NULL);
	while (*str0 && ft_strchr(set, *str0))
		str0++;
	cnt = ft_strlen(str0) + 1;
	while (cnt && ft_strchr(set, str0[cnt - 1]))
		cnt--;
	nwstr = (char *) malloc((cnt + 1) * sizeof(char));
	if (!nwstr)
		return (NULL);
	ft_strlcpy(nwstr, str0, cnt + 1);
	return (nwstr);
}
