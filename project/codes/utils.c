/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgomes-p <vgomes-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 16:10:30 by vgomes-p          #+#    #+#             */
/*   Updated: 2025/02/13 16:55:00 by vgomes-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**dup_env(char **envp, size_t *envsz)
{
	char	**nwenv;
	int		cnt;
	int		pos;

	cnt = 0;
	if (envp)
		while (envp[cnt])
			cnt++;
	*envsz = cnt;
	nwenv = ft_calloc(cnt + 1, sizeof(char *));
	if (!nwenv)
		return (NULL);
	pos = -1;
	while (++pos < cnt)
	{
		nwenv[pos] = ft_strdup(envp[pos]);
		if (!nwenv[pos])
		{
			while (--pos >= 0)
				free(nwenv[pos]);
			free(nwenv);
			return (NULL);
		}
	}
	return (nwenv);
}

void	free_env(char **env)
{
	int	pos;

	if(!env)
		return ;
	pos = 0;
	while (env[pos])
	{
		free(env[pos]);
		pos++;
	}
	free(env);
}
