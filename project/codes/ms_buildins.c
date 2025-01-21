/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_buildins.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgomes-p <vgomes-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 18:11:40 by vgomes-p          #+#    #+#             */
/*   Updated: 2025/01/21 15:40:20 by vgomes-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	execute_builtin_command(char **tokens, t_minishell *shell)
{
	if (lms_strcmp(tokens[0], "echo") == 0)
		ms_echo(tokens);
	else if (lms_strcmp(tokens[0], "env") == 0)
		ms_env();
	else if (lms_strcmp(tokens[0], "unset") == 0)
		ms_unset(&(shell->env), tokens);
	else if (lms_strcmp(tokens[0], "export") == 0)
		ms_export(&(shell->env), tokens);
	else if (lms_strcmp(tokens[0], "pwd") == 0)
		ms_pwd();
	else if (lms_strcmp(tokens[0], "cd") == 0)
		ms_cd(tokens);
	else
		ms_error("\033[1;31mcommand not found!\n\033[0m", shell);
}

static void	cleanup_tokens(char **tokens)
{
	int	index;

	index = 0;
	while (tokens && tokens[index])
	{
		free(tokens[index]);
		index++;
	}
	free(tokens);
}

void	ms_process_buildin(char *input, t_minishell *shell)
{
	char	**tokens;

	ms_tokenize_input(input, &tokens, shell);
	if (tokens && tokens[0])
		execute_builtin_command(tokens, shell);
		
	cleanup_tokens(tokens);
}
