/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgomes-p <vgomes-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 13:20:17 by vgomes-p          #+#    #+#             */
/*   Updated: 2025/01/30 12:31:27 by vgomes-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ms_unset(char ***env, char **args)
{
	if (args[1])
	{
		if (lms_unsetenv(env, args[1]) == -1)
			ft_putstr_fd("unset: " RED "error unsetting variable\n" RESET, 2);
	}
	else
		ft_putstr_fd("unset: not enough args\nusage: unset VAR\n", 2);
}
