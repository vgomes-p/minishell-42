/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgomes-p <vgomes-p@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 16:23:37 by vgomes-p          #+#    #+#             */
/*   Updated: 2025/03/19 04:12:58 by vgomes-p         ###   ########.fr       */
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
	if (!shell.env)
	{
		ft_putstr_fd(RED "Error: Failed to duplicate env\n" RESET, 2);
		return (1);
	}
	shell.prompt = NULL;
	shell.exit_stt = 0;
	shell.cancelled_cmd = 0;
	shell.tokens = NULL;
	shell.should_exit = 0;
	g_shell = &shell;
	signal(SIGINT, interactive_signal_handler);
	signal(SIGQUIT, SIG_IGN);
	welcome();
	while (ms_prompt(&shell) == 0)
		continue ;
	cleanup_all(&shell);
	return (shell.exit_stt);
}
