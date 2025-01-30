/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgomes-p <vgomes-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 12:53:08 by vgomes-p          #+#    #+#             */
/*   Updated: 2024/11/07 12:53:08 by vgomes-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t num_el, size_t numby)
{
	void	*memaloc;
	size_t	finsize;

	memaloc = NULL;
	finsize = num_el * numby;
	if (num_el == 0 || numby == 0 || finsize / num_el != numby)
		return (NULL);
	memaloc = malloc(finsize);
	if (memaloc)
		ft_bzero(memaloc, finsize);
	return (memaloc);
}
