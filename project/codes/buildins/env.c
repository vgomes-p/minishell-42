/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgomes-p <vgomes-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 16:13:56 by vgomes-p          #+#    #+#             */
/*   Updated: 2025/02/05 15:15:27 by vgomes-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern char	**environ;

void	ms_env(void)
{
	int	curr_arg;

	curr_arg = 0;
	while (environ[curr_arg])
	{
		lms_putstr(environ[curr_arg]);
		lms_putstr("\n");
		curr_arg++;
	}
}
