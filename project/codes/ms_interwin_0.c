/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_interwin_0.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgomes-p <vgomes-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 15:00:10 by vgomes-p          #+#    #+#             */
/*   Updated: 2025/01/13 19:19:35 by vgomes-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ms_inishell(t_minishell *shell)
{
	shell->prompt = ft_strdup("\033[1;33mminishell$ >\033[0m ");
	if (!shell->prompt)
	{
		perror("Error initializing prompt");
		exit (1);
	}
}

void	ms_interwin(t_minishell *shell)
{
	char	*input;
	char	*can_move;

	ms_window(shell);
	can_move = tgetstr("can_move", NULL);
	if (!can_move)
	{
		perror("Error getting cursor movement capability");
		exit (1);
	}
	while (1)
	{
		tputs(tgoto(can_move, 2, shell->term_height - 2), 1, putchar);
		input = readline(shell->prompt);
		if (!input)
		{
			printf("exit\n");
			break ;
		}
		if (*input)
			add_history(input);
		free(input);
	}
	rl_clear_history();
}
