/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgomes-p <vgomes-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 17:41:31 by vgomes-p          #+#    #+#             */
/*   Updated: 2025/01/31 14:25:13 by vgomes-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**dup_env(char **envp, size_t *envsz)
{
	char	**nwenv;
	int		cnt;
	int		index;

	cnt = 0;
	if (envp)
		while (envp[cnt])
			cnt++;
	*envsz = cnt;
	nwenv = ft_calloc(cnt + 1, sizeof(char *));
	if (!nwenv)
		return (NULL);
	index = -1;
	while (++index < cnt)
	{
		nwenv[index] = ft_strdup(envp[index]);
		if (!nwenv[index])
		{
			while (--index >= 0)
				free(nwenv[index]);
			free(nwenv);
			return (NULL);
		}
	}
	return (nwenv);
}
