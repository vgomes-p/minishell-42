/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgomes-p <vgomes-p@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 16:10:30 by vgomes-p          #+#    #+#             */
/*   Updated: 2025/03/18 17:21:39 by vgomes-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	cleanup_all(t_minishell *shell)
{
	free_env(shell->env);
	free(shell->prompt);
	free_tokens(shell->tokens);
	rl_clear_history();
}

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

void	interactive_signal_handler(int sig)
{
	if (sig == SIGINT)
	{
		lms_putchar('\n');
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}
