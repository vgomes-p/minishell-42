/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgomes-p <vgomes-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 16:10:30 by vgomes-p          #+#    #+#             */
/*   Updated: 2025/02/21 12:03:54 by vgomes-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	dup_env_str(char **nwenv, char **envp, size_t cnt)
{
	size_t	pos;

	pos = 0;
	while (pos < cnt)
	{
		nwenv[pos] = ft_strdup(envp[pos]);
		if (!nwenv[pos])
		{
			while (--pos > 0)
				free(nwenv[--pos]);
			free(nwenv);
			return (0);
		}
		pos++;
	}
	nwenv[cnt] = NULL;
	return (1);
}

char	**dup_env(char **envp, size_t *envsz)
{
	char	**nwenv;
	size_t	cnt;

	if (!envp || !envsz)
		return (NULL);
	cnt = 0;
	while (envp[cnt])
		cnt++;
	*envsz = cnt;
	nwenv = ft_calloc(cnt + 1, sizeof(char *));
	if (!nwenv)
		return (NULL);
	if (!dup_env_str(nwenv, envp, cnt))
		return (NULL);
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
