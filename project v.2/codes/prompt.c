/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgomes-p <vgomes-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 16:23:34 by vgomes-p          #+#    #+#             */
/*   Updated: 2025/01/30 16:52:56 by vgomes-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*pathedprompt(t_minishell *shell)
{
	(void)shell;
	char	*cwd;
	char	*home;
	char	*relative_cwd;
	char	*prompt;

	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		perror("getcwd");
		return (NULL);
	}
	home = getenv("HOME");
	if (home && lms_strstr(cwd, home) == cwd)
	{
		relative_cwd = ft_strjoin("~", cwd + ft_strlen(home));
		free(cwd);
		cwd = relative_cwd;
	}
	prompt = ft_strjoin(GREEN, cwd);
	prompt = lms_strjoin_free(prompt, RESET);
	prompt = lms_strjoin_free(prompt, CYAN " minishell$ " RESET);
	free(cwd);
	return (prompt);
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
	t_token	*tokens;
	char	*prompt;

	prompt = pathedprompt(shell);
	if (!prompt)
	{
		ft_putstr_fd(RED "Error: Failed to generate prompt\n" RESET, 2);
		return ;
	}
	input = readline(prompt);
	free(prompt);
	if (!input)
	{
		ft_putstr_fd(RED "\nSee you soon, goodbye!\n" RESET, 1);
		free(shell->prompt);
		exit(shell->exit_stt);
	}
	if (input[0] == '\0')
	{
		free(input);
		return ;
	}
	shell->prompt = input;
	tokens = tokening(input);
	if (!tokens)
	{
		ft_putstr_fd(RED "Error: Tokenination has failed\n" RESET, 2);
		return ;
	}
	if (!valid_syntax(tokens))
	{
		ft_putstr_fd(RED "Syntax error\n" RESET, 2);
		free_tokens(tokens);
		return ;
	}
	if (exec_builtin(tokens, shell) == 0)
		exec_extern(tokens, shell);
	free(input);
	free_tokens(tokens);
	rl_clear_history();
}