/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_buildins_6.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgomes-p <vgomes-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 17:33:04 by vgomes-p          #+#    #+#             */
/*   Updated: 2025/01/21 16:45:20 by vgomes-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ms_unset(char ***env, char **args)
{
	if (args[1])
	{
		if (lms_unsetenv(env, args[1]) == -1)
			ft_putstr_fd("unset: \033[1;31merror unsetting variable\033[0m\n", 2);
	}
	else
		ft_putstr_fd("unset: not enough args\nusage: unset VAR\n", 2);
}

void	ms_pwd(void)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (cwd)
	{
		lms_putstr(cwd);
		lms_putstr("\n");
		free(cwd);
	}
	else
		ft_putstr_fd("pwd: \033[1;31merror\033[0m\n", 2);
}
