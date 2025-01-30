/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgomes-p <vgomes-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 13:22:26 by vgomes-p          #+#    #+#             */
/*   Updated: 2025/01/30 12:29:24 by vgomes-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ms_cd(char **args)
{
	char	*home;

	if (!args[1])
	{
		home = getenv("HOME");
		if (home)
			chdir(home);
		else
			ft_putstr_fd("cd: " RED "HOME not set" RESET, 2);
	}
	else
	{
		if (chdir(args[1]) == -1)
			perror("cd");
	}
}
