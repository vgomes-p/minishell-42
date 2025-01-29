/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgomes-p <vgomes-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 12:55:26 by vgomes-p          #+#    #+#             */
/*   Updated: 2024/11/07 12:55:26 by vgomes-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *str, void (*ftn)(unsigned int, char*))
{
	int		cnt;

	cnt = -1;
	while (str[++cnt])
		ftn(cnt, &str[cnt]);
}
