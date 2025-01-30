/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lms_setenv.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgomes-p <vgomes-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 14:00:34 by vgomes-p          #+#    #+#             */
/*   Updated: 2025/01/16 17:13:43 by vgomes-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libms.h"

static int	create_env_string(const char *name,
							const char *value, char **result)
{
	char	*env_in;

	if (!name || !value || !result)
		return (-1);
	env_in = ft_strjoin(name, "=");
	if (!env_in)
		return (-1);
	*result = ft_strjoin(env_in, value);
	free(env_in);
	if (!(*result))
		return (-1);
	return (0);
}

static int	update_existing_env(char **env, const char *name,
							char *env_in, int overwrite)
{
	int	index;

	index = 0;
	while (env[index])
	{
		if (ft_strncmp(env[index], name, ft_strlen(name)) == 0
			&& env[index][ft_strlen(name)] == '=')
		{
			if (overwrite)
			{
				free(env[index]);
				env[index] = env_in;
			}
			else
				free(env_in);
			return (1);
		}
		index++;
	}
	return (0);
}

static int	add_new_env(char ***env, char *env_in, int env_size)
{
	*env = lms_realloc(*env, sizeof(char *) * (env_size + 2));
	if (!(*env))
	{
		free(env_in);
		return (-1);
	}
	(*env)[env_size] = env_in;
	(*env)[env_size + 1] = NULL;
	return (0);
}

int	lms_setenv(char ***env, const char *name, const char *value, int overwrite)
{
	char	*env_in;
	int		env_size;

	if (create_env_string(name, value, &env_in) == -1)
		return (-1);
	if (!env || !*env)
	{
		free(env_in);
		return (-1);
	}
	if (update_existing_env(*env, name, env_in, overwrite))
		return (0);
	env_size = 0;
	while ((*env)[env_size])
		env_size++;
	return (add_new_env(env, env_in, env_size));
}
