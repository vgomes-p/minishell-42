/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgomes-p <vgomes-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 16:23:37 by vgomes-p          #+#    #+#             */
/*   Updated: 2025/02/18 14:09:11 by vgomes-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
	signal(SIGINT, handle_signal);
	signal(SIGQUIT, handle_signal);
	welcome();
	while (1)
	{
		ms_prompt(&shell);
	}
	free_env(shell.env);
	return (0);
}
