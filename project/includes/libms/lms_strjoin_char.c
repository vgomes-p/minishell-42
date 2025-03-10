/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lms_strjoin_char.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgomes-p <vgomes-p@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 13:36:13 by vgomes-p          #+#    #+#             */
/*   Updated: 2025/03/10 14:11:48 by vgomes-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libms.h"

char	*lms_strjoin_char(char const *str0, char ch)
{
	char	*result;
	size_t	len;
	size_t	pos;

	if (!str0)
		return (NULL);
	len = ft_strlen(str0);
	result = (char *)malloc(len + 2);
	if (!result)
		return (NULL);
	pos = 0;
	while (str0[pos])
	{
		result[pos] = str0[pos];
		pos++;
	}
	result[pos] = ch;
	result[pos + 1] = '\0';
	return (result);
}
