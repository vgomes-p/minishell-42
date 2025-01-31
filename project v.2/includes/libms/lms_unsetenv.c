/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lms_unsetenv.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgomes-p <vgomes-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 14:00:45 by vgomes-p          #+#    #+#             */
/*   Updated: 2025/01/31 14:23:29 by vgomes-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libms.h"

static void	shift_env_vars(char **env, int start_index)
{
	if (!env || start_index < 0)
		return ;
	while (env[start_index + 1])
	{
		env[start_index] = env[start_index + 1];
		start_index++;
	}
	env[start_index] = NULL;
}

int	lms_unsetenv(char ***env, const char *name, size_t *env_size)
{
	int	index;

	if (!env || !name || !(*env))
		return (-1);
	index = lms_find_env_var(*env, name);
	if (index == -1)
		return (-1);
	free((*env)[index]);
	shift_env_vars(*env, index);
	(*env_size)--;
	return (0);
}
