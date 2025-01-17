/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_buildins_4.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgomes-p <vgomes-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 17:32:58 by vgomes-p          #+#    #+#             */
/*   Updated: 2025/01/17 13:23:06 by vgomes-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern char	**environ;

void	ms_env(void)
{
	int	index;

	index = 0;
	while (environ[index])
	{
		lms_putstr(environ[index]);
		lms_putstr("\n");
		index++;
	}
}
