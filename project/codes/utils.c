/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgomes-p <vgomes-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 16:10:30 by vgomes-p          #+#    #+#             */
/*   Updated: 2025/02/18 14:18:45 by vgomes-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**dup_env(char **envp, size_t *envsz)
{
	char	**nwenv;
	size_t		cnt;
	size_t		pos;

	if (!envp || !envsz)
		return (NULL);
	cnt = 0;
	while (envp[cnt])
		cnt++;
	*envsz = cnt;
	nwenv = ft_calloc(cnt + 1, sizeof(char *));
	if (!nwenv)
		return (NULL);
	pos = 0;
	while (pos < cnt)
	{
		nwenv[pos] = ft_strdup(envp[pos]);
		if (!nwenv[pos])
		{
			while (--pos > 0)
				free(nwenv[--pos]);
			free(nwenv);
			return (NULL);
		}
		pos++;
	}
	nwenv[cnt] = NULL;
	return (nwenv);
}

void	handle_signal(int sig)
{
	(void)sig;
	if (g_shell->env)
	{
		free_env(g_shell->env);
		g_shell->env = NULL;
	}
	exit(0);
}
