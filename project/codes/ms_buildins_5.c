/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_buildins_5.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgomes-p <vgomes-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 17:33:01 by vgomes-p          #+#    #+#             */
/*   Updated: 2025/01/14 18:51:46 by vgomes-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern char	**environ;

void	ms_export(char **args)
{
	char	*equal_sign;
	int		index;

	if (args[1])
	{
		equal_sign = ft_strchr(args[1], '=');
		if (equal_sign)
		{
			*equal_sign = '\0';
			setenv(args[1], equal_sign + 1, 1);
		}
		else
		{
			index = 0;
			while (environ[index])
			{
				ft_putstr(environ[index]);
				ft_putstr("\n");
				index++;
			}
		}
	}
	else
		ft_putstr_fd("export: usage: export VAR+VALUE\n", 2);
}
