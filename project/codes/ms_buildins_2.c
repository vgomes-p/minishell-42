/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_buildins_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgomes-p <vgomes-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 17:32:50 by vgomes-p          #+#    #+#             */
/*   Updated: 2025/01/17 13:22:47 by vgomes-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ms_echo(char **args)
{
	int	index;
	int	nwline;

	index = 1;
	nwline = 1;
	if (args[1] && lms_strcmp(args[1], "-n") == 0)
	{
		nwline = 0;
		index++;
	}
	while (args[index])
	{
		lms_putstr(args[index]);
		if (args[index + 1])
			lms_putstr(" ");
		index++;
	}
	if (nwline)
		lms_putstr("\n");
}
