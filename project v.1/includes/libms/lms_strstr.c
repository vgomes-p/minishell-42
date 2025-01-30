/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lms_strstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgomes-p <vgomes-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 16:53:22 by vgomes-p          #+#    #+#             */
/*   Updated: 2025/01/22 17:01:53 by vgomes-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libms.h"

char	*lms_strstr(const char *haystack, const char *needle)
{
	size_t	h_index;
	size_t	n_index;

	if (*needle == '\0')
		return ((char *)haystack);
	h_index = 0;
	while (haystack[h_index] != '\0')
	{
		n_index = 0;
		while (haystack[h_index + n_index] == needle[n_index]
			&& needle[n_index] != '\0')
			n_index++;
		if (needle[n_index] == '\0')
			return ((char *)(haystack + h_index));
		h_index++;
	}
	return (NULL);
}
