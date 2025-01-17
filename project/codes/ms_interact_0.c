/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_interact_0.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgomes-p <vgomes-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 15:00:10 by vgomes-p          #+#    #+#             */
/*   Updated: 2025/01/17 13:21:14 by vgomes-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ms_inishell(t_minishell *shell)
{
	shell->prompt = ft_strdup("\033[1;36mminishell$ > \033[0m");
	if (!shell->prompt)
	{
		perror("\033[1;31mError initializing prompt\033[0m");
		exit (1);
	}
	lms_putstr("                         \033[1;7;36m");
	lms_putstr("{Made by vgomes-p & sthrodri\033[0m\n\n");
	lms_putstr("\n\033[1;36m╔═════════════════════════════════════");
	lms_putstr("═════════════════════════════════════════╗\n");
	lms_putstr("║                            WELCOME T");
	lms_putstr("O MINISHELL                              ║\n");
	lms_putstr("╚══════════════════════════════════════");
	lms_putstr("════════════════════════════════════════╝\033[0m\n");
}

void	ms_interact0(t_minishell *shell)
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
