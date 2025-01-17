/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_buildins_7.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgomes-p <vgomes-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 18:10:28 by vgomes-p          #+#    #+#             */
/*   Updated: 2025/01/17 13:24:27 by vgomes-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
