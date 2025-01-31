/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lms_find_env_var.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgomes-p <vgomes-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 14:18:42 by vgomes-p          #+#    #+#             */
/*   Updated: 2025/01/31 14:21:24 by vgomes-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libms.h"

int	lms_find_env_var(char **env, const char *name)
{
	int	index;
	size_t	nmlen;

	if (!env || !name)
		return (-1);
	nmlen = ft_strlen(name);
	index = 0;
	while (env[index])
	{
		if (ft_strncmp(env[index], name, nmlen) == 0
			&& env[index][nmlen] == '=')
			return (index);
		index++;
	}
	return (-1);
}