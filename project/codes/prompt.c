/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgomes-p <vgomes-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 16:23:34 by vgomes-p          #+#    #+#             */
/*   Updated: 2025/01/27 13:50:58 by vgomes-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	pathedprompt(t_minishell *shell)
{
	char	*cwd;
	char	*home;
	char	*relative_cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		perror("getcwd");
		return ;
	}
	home = getenv("HOME");
	if (home && lms_strstr(cwd, home) == cwd)
	{
		relative_cwd = ft_strjoin("~", cwd + ft_strlen(home));
		free(cwd);
		cwd = relative_cwd;
	}
	free(shell->prompt);
	shell->prompt = ft_strjoin(GREEN, cwd);
	shell->prompt = lms_strjoin_free(shell->prompt, RESET);
	shell->prompt = lms_strjoin_free(shell->prompt, CYAN " minishell$ " RESET);
	free(cwd);
}

void	welcome(void)
{
	lms_putstr("                         ");
	lms_putstr(RECYAN "{Made by vgomes-p & sthrodri}" RESET "\n\n");
	lms_putstr("\n" CYAN "╔═════════════════════════════════════");
	lms_putstr("═════════════════════════════════════════╗\n");
	lms_putstr("║                            WELCOME T");
	lms_putstr("O MINISHELL                              ║\n");
	lms_putstr("╚══════════════════════════════════════");
	lms_putstr("════════════════════════════════════════╝" RESET "\n");
}

void	ms_prompt(t_minishell *shell)
{
	char	*input;

	while (1)
	{
		pathedprompt(shell);
		input = readline(shell->prompt);
		if (!input)
		{
			printf(RED "exit" RESET "\n");
			break ;
		}
		if (*input)
			add_history(input);
		free(input);
	}
	rl_clear_history();
}
