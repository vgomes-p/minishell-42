/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lms_realloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgomes-p <vgomes-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 14:21:44 by vgomes-p          #+#    #+#             */
/*   Updated: 2025/01/31 14:13:11 by vgomes-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libms.h"

void	*lms_realloc(void *ptr, size_t oldsz, size_t nwsize)
{
	void	*nwptr;

	if (!ptr)
		return (malloc(nwsize));
	if (nwsize == 0)
	{
		free(ptr);
		return (NULL);
	}
	nwptr = malloc(nwsize);
	if (!nwptr)
	{
		free(ptr);
		return (NULL);
	}
	ft_memcpy(nwptr, ptr, oldsz < nwsize ? oldsz : nwsize);
	free(ptr);
	return (nwptr);
}
