/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_buildins_6.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgomes-p <vgomes-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 17:33:04 by vgomes-p          #+#    #+#             */
/*   Updated: 2025/01/16 16:22:14 by vgomes-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ms_unset(char ***env, char **args)
{
	if (args[1])
	{
		if (ft_unsetenv(env, args[1]) == -1)
			ft_putstr_fd("unset: \033[1;31merror unsetting variable\033[0m\n", 2);
	}
	else
		ft_putstr_fd("unset: not enough args\nusage: unset VAR\n", 2);
}
