/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgomes-p <vgomes-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 13:20:59 by vgomes-p          #+#    #+#             */
/*   Updated: 2025/01/28 13:41:59 by vgomes-p         ###   ########.fr       */
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
