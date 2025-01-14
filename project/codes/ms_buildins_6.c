/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_buildins_6.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgomes-p <vgomes-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 17:33:04 by vgomes-p          #+#    #+#             */
/*   Updated: 2025/01/14 18:10:03 by vgomes-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ms_unset(char **args)
{
	if (args[1])
	{
		unsetenv(args[1]);
	}
	else
		ft_putstr_fd("unset: usage: unset VAR\n", 2);
}
