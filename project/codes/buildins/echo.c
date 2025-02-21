/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sthrodri <sthrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 16:12:45 by vgomes-p          #+#    #+#             */
/*   Updated: 2025/02/21 13:31:09 by sthrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ms_echo(char **args)
{
	int	curr_arg;
	int	nwline;

	curr_arg = 1;
	nwline = 1;
	while (args[curr_arg] && lms_strcmp(args[curr_arg], "-n") == 0)
	{
		nwline = 0;
		curr_arg++;
	}
	print_echo_args(args, curr_arg);
	if (nwline)
		ft_putstr_fd("\n", STDOUT_FILENO);
}
