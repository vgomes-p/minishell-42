/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgomes-p <vgomes-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 13:20:40 by vgomes-p          #+#    #+#             */
/*   Updated: 2025/01/30 12:30:17 by vgomes-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	display_environment(char **env)
{
	int	index;

	index = 0;
	while (env[index])
	{
		lms_putstr(env[index]);
		lms_putstr("\n");
		index++;
	}
}

static int	handle_variable_assignment(char ***env, char *arg)
{
	char	*equal_sign;

	equal_sign = ft_strchr(arg, '=');
	if (!equal_sign)
		return (0);
	*equal_sign = '\0';
	if (lms_setenv(env, arg, equal_sign + 1, 1) == -1)
	{
		ft_putstr_fd("export: " RED "merror setting variable" RESET, 2);
		*equal_sign = '=';
		return (-1);
	}
	*equal_sign = '=';
	return (1);
}

void	ms_export(char ***env, char **args)
{
	if (!args[1])
	{
		ft_putstr_fd("export: not enough args\nusage: export VAR=VALUE\n", 2);
		return ;
	}
	if (handle_variable_assignment(env, args[1]) == 0)
		display_environment(*env);
}
