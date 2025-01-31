/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgomes-p <vgomes-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 13:20:17 by vgomes-p          #+#    #+#             */
/*   Updated: 2025/01/31 14:37:35 by vgomes-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ms_unset(char ***env, char **args, size_t *env_size)
{
	if (!args[1])
	{
		ft_putstr_fd("unset: " YELLOW "missing arguments\n" RESET, 2);
		return (0);
	}
	if (lms_unsetenv(env, args[1], env_size) == -1)
	{
		ft_putstr_fd("unset: " RED "error unsetting variable\n" RESET, 2);
		return (-1);
	}
	return (0);
}
