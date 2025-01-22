/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgomes-p <vgomes-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 16:23:34 by vgomes-p          #+#    #+#             */
/*   Updated: 2025/01/22 17:20:01 by vgomes-p         ###   ########.fr       */
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
	shell->prompt = ft_strjoin("\033[1;32m", cwd);
	shell->prompt = lms_strjoin_free(shell->prompt, "\033[0m");
	shell->prompt = lms_strjoin_free(shell->prompt, "\033[1;36m | minishell$ \033[0m");
	free(cwd);
}

void	welcome(t_minishell *shell)
{
	shell->prompt = ft_strdup("\033[1;36m | minishell$ \033[0m");
	if (!shell->prompt)
	{
		perror("\033[1;31Error starting prompt\033[0m");
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

void	ms_prompt(t_minishell *shell)
{
	char	*input;

	while (1)
	{
		pathedprompt(shell);
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
