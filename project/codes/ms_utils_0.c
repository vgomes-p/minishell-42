/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_utils_0.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgomes-p <vgomes-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 18:29:48 by vgomes-p          #+#    #+#             */
/*   Updated: 2025/01/14 14:20:46 by vgomes-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_putchar(char ch)
{
	write(1, &ch, 1);
}

void	ft_putstr(char *str)
{
	if (str)
	{
		while (*str)
		{
			write(1,str, 1);
			str++;
		}
	}
}
