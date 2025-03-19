/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgomes-p <vgomes-p@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 16:23:34 by vgomes-p          #+#    #+#             */
/*   Updated: 2025/03/19 13:44:20 by vgomes-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*pathedprompt(t_minishell *shell)
{
	char	*cwd;
	char	*home;
	char	*relative_cwd;
	char	*prompt;

	(void)shell;
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
	prompt = lms_strjoin_free(prompt, CYAN " minishell$ > " RESET);
	free(cwd);
	return (prompt);
}

static void	handle_input(t_minishell *shell, char **input)
{
	char	*prompt;

	prompt = pathedprompt(shell);
	if (!prompt)
	{
		ft_putstr_fd(RED "Error: Failed to generate prompt\n" RESET, 2);
		return ;
	}
	*input = readline(prompt);
	free(prompt);
	if (!*input)
	{
		ft_putstr_fd(RECYAN "\n\n\nSee you soon, goodbye!\n\n\n" RESET, 1);
		free(shell->prompt);
		free_env(shell->env);
		rl_clear_history();
		exit(shell->exit_stt);
	}
	if ((*input)[0] == '\0')
	{
		free(*input);
		*input = NULL;
		return ;
	}
	add_history(*input);
}

static int	pre_process_tks(char *input, t_minishell *shell)
{
	shell->tokens = tokening(input);
	if (!shell->tokens)
	{
		ft_putstr_fd(RED "Error: Tokenination has failed\n" RESET, 2);
		shell->exit_stt = 2;
		free(input);
		return (0);
	}
	if (!valid_syntax(shell->tokens))
	{
		ft_putstr_fd(RED "Syntax error\n" RESET, 2);
		free_tokens(shell->tokens);
		shell->tokens = NULL;
		shell->exit_stt = 2;
		free(input);
		return (0);
	}
	return (1);
}

static void	process_command(char *input, t_minishell *shell)
{
	t_token	*current;
	t_token	*prev;
	char	*nw_value;

	if (!pre_process_tks(input, shell))
		return ;
	current = shell->tokens;
	prev = NULL;
	while (current)
	{
		if ((current->type == CMD || current->type == ARG)
			&& (!prev || prev->type != HEREDOC))
		{
			nw_value = expand_var(shell, current->value);
			current->value = nw_value;
		}
		prev = current;
		current = current->next;
	}
	exec_cmd(shell);
	free_tokens(shell->tokens);
	shell->tokens = NULL;
	free(input);
}

int	ms_prompt(t_minishell *shell)
{
	char	*input;

	if (shell->tokens)
	{
		free_tokens(shell->tokens);
		shell->tokens = NULL;
	}
	handle_input(shell, &input);
	if (input)
		process_command(input, shell);
	if (shell->should_exit)
		return (1);
	return (0);
}
