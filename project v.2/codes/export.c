/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgomes-p <vgomes-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 13:20:40 by vgomes-p          #+#    #+#             */
/*   Updated: 2025/01/31 14:35:38 by vgomes-p         ###   ########.fr       */
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

static int	handle_variable_assignment(char ***env, char *arg, size_t *env_size)
{
	char	*equal_sign;
	char	*name;
	char	*value;
	int		ret;

	if (!env || !arg || !env_size)
		return (-1);
	equal_sign = ft_strchr(arg, '=');
	if (!equal_sign)
		return (0);
	name = ft_substr(arg, 0,equal_sign - arg);
	if (!name)
		return (-1);
	value = ft_strdup(equal_sign + 1);
	if (!value)
	{
		free(name);
		return (-1);
	}
	ret = lms_setenv(env, name, value, 1, env_size);
	free(name);
	free(value);
	return (ret);
}

void	ms_export(char ***env, char **args, size_t *env_size)
{
	if (!args[1])
	{
		display_environment(*env);
		return ;
	}
	if (handle_variable_assignment(env, args[1], env_size) == 0)
		display_environment(*env);
}
