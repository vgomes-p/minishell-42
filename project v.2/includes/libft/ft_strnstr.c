/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgomes-p <vgomes-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 12:56:31 by vgomes-p          #+#    #+#             */
/*   Updated: 2024/11/07 12:56:31 by vgomes-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *ltl, size_t lench)
{
	size_t	lenb;
	size_t	lenl;

	lenb = 0;
	lenl = ft_strlen(ltl);
	if (lenl == 0)
		return ((char *)big);
	while (*big && lenb <= lench)
	{
		if (lench - lenb++ >= lenl && !ft_strncmp(big, ltl, lenl))
			return ((char *)big);
		big++;
	}
	return (0);
}
