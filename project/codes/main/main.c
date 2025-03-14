/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgomes-p <vgomes-p@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 16:23:37 by vgomes-p          #+#    #+#             */
/*   Updated: 2025/03/11 16:32:18 by vgomes-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_minishell	*g_shell = NULL;

int	main(int argc, char **argv, char **envp)
{
	t_minishell	shell;

	(void)argc;
	(void)argv;
	shell.env = dup_env(envp, &shell.env_size);
	shell.prompt = NULL;
	shell.exit_stt = 0;
	g_shell = &shell;
	signal(SIGINT, interactive_signal_handler);
	signal(SIGQUIT, SIG_IGN);
	welcome();
	while (1)
	{
		ms_prompt(&shell);
	}
	free_env(shell.env);
	return (0);
}
