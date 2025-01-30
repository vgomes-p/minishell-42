/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lms_strndup.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgomes-p <vgomes-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 14:36:56 by vgomes-p          #+#    #+#             */
/*   Updated: 2025/01/21 14:39:05 by vgomes-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libms.h"

char	*lms_strndup(const char *str, size_t n)
{
	char	*dup;

	dup = (char *)malloc(n + 1);
	if (!dup)
		return (NULL);
	lms_strncpy(dup, str, n);
	dup[n] = '\0';
	return (dup);
}
