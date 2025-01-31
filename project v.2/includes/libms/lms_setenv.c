/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lms_setenv.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgomes-p <vgomes-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 14:00:34 by vgomes-p          #+#    #+#             */
/*   Updated: 2025/01/31 14:48:16 by vgomes-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libms.h"
static int	add_new_env(char ***env, char *env_in, int *env_size)
{
	char	**nwenv;

	if (!env || !env_in || !env_size)
		return (-1);
	nwenv = lms_realloc(*env, *env_size * sizeof(char *), (*env_size + 2) * sizeof(char *));
	if (!nwenv)
	{
		return (-1);
	}
	nwenv[*env_size] = env_in;
	nwenv[*env_size + 1] = NULL;
	*env = nwenv;
	(*env_size)++;
	return (0);
}

int	lms_setenv(char ***env, const char *name, const char *value, int overwrite, size_t *envsz)
{
	char	*env_in;
	int		index;

	if (!env || !name || !value || !envsz)
		return (-1);
	env_in = ft_strjoin(name, "=");
	if (!env_in)
		return (-1);
	env_in = lms_strjoin_free(env_in, (char *)value);
	if (!env_in)
		return (-1);
	index = lms_find_env_var(*env, name);
	if (index != -1)
	{
		if (overwrite)
		{
			free((*env)[index]);
			(*env)[index] = env_in;
		}
		else
			free(env_in);
		return (0);
	}
	if (add_new_env(env, env_in, (int *)envsz) == -1)
	{
		free(env_in);
		return (-1);
	}
	return (0);
}
