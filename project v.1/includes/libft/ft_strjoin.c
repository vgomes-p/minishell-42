/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgomes-p <vgomes-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 12:55:31 by vgomes-p          #+#    #+#             */
/*   Updated: 2024/11/07 12:55:31 by vgomes-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *str0, char const *str1)
{
	char	*nwstr;
	size_t	len0;
	size_t	len1;

	len0 = ft_strlen(str0);
	len1 = ft_strlen(str1);
	nwstr = malloc((len0 + len1 + 1) * sizeof(char));
	if (nwstr == NULL)
		return (NULL);
	ft_strlcpy(nwstr, str0, len0 + 1);
	ft_strlcpy(&nwstr[len0], str1, len1 + 1);
	return (nwstr);
}
