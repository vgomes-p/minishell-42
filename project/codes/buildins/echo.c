/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgomes-p <vgomes-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 16:12:45 by vgomes-p          #+#    #+#             */
/*   Updated: 2025/02/05 15:15:11 by vgomes-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ms_echo(char **args)
{
	int	curr_arg;
	int	nwline;

	curr_arg = 1;
	nwline = 1;
	if (args[1] && lms_strcmp(args[1], "-n") == 0)
	{
		nwline = 0;
		curr_arg++;
	}
	while (args[curr_arg])
	{
		lms_putstr(args[curr_arg]);
		if (args[curr_arg + 1])
			lms_putstr(" ");
		curr_arg++;
	}
	if (nwline)
		lms_putstr("\n");
}
