/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_interwin_0.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgomes-p <vgomes-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 15:00:10 by vgomes-p          #+#    #+#             */
/*   Updated: 2025/01/14 19:01:35 by vgomes-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ms_inishell(t_minishell *shell)
{
	shell->prompt = ft_strdup("\033[1;36mminishell$ > \033[0m");
	if (!shell->prompt)
	{
		perror("Error initializing prompt");
		exit (1);
	}
	ft_putstr("                         \033[1;7;36m");
	ft_putstr("{Made by vgomes-p & sthrodri\033[0m\n\n");
	ft_putstr("\n\033[1;36m╔═════════════════════════════════════");
	ft_putstr("═════════════════════════════════════════╗\n");
	ft_putstr("║                            WELCOME T");
	ft_putstr("O MINISHELL                              ║\n");
	ft_putstr("╚══════════════════════════════════════");
	ft_putstr("════════════════════════════════════════╝\033[0m\n");
}

void	ms_interwin(t_minishell *shell)
{
	char	*input;

	while (1)
	{
		input = readline(shell->prompt);
		if (!input)
		{
			printf("exit\n");
			break ;
		}
		if (*input)
			add_history(input);
		ms_process_buildin(input, shell);
		free(input);
	}
	rl_clear_history();
}
