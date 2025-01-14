/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_interwin_0.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgomes-p <vgomes-p@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 15:00:10 by vgomes-p          #+#    #+#             */
/*   Updated: 2025/01/14 02:07:33 by vgomes-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ms_inishell(t_minishell *shell)
{
	shell->prompt = ft_strdup("\033[1;7;36mminishell$ >\033[0m ");
	if (!shell->prompt)
	{
		perror("Error initializing prompt");
		exit (1);
	}
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
		free(input);
	}
	rl_clear_history();
}
