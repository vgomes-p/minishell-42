/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgomes-p <vgomes-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 16:36:18 by vgomes-p          #+#    #+#             */
/*   Updated: 2025/01/31 14:24:15 by vgomes-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	exec_extern(t_token *tokens, t_minishell *shell)
{
	char	**args;
	pid_t	pid;
	int		index0;
	t_token	*current;

	args = malloc(sizeof(char *) * (count_tokens(tokens) + 1));
	if (!args)
		return ;
	current = tokens;
	index0 = 0;
	while (current)
	{
		args[index0++] = current->value;
		current = current->next;
	}
	args[index0] = NULL;
	pid = fork();
	if (pid == 0)
	{
		if (execve(args[0], args, shell->env) == -1)
		{
			perror(RED "execve" RESET);
			exit(EXIT_FAILURE);
		}
	}
	else if (pid < 0)
		perror(RED "fork" RESET);
	else
		waitpid(pid, NULL, 0);/*colocar WNOHANG no lugar do 0 se der timeout*/
	free(args);
}

int	exec_builtin(t_token *tokens, t_minishell *shell)
{
	char	**args;
	t_token	*current;
	int		index0;

	current = tokens;
	args = malloc(sizeof(char *) * (count_tokens(tokens) + 1));
	if (!args)
		return (-1);
	index0 = 0;
	while (current)
	{
		args[index0++] = current->value;
		current = current->next;
	}
	args[index0] = NULL;

	if (lms_strcmp(args[0], "cd") == 0)
		ms_cd(args);
	else if (lms_strcmp(args[0], "echo") == 0)
		ms_echo(args);
	else if (lms_strcmp(args[0], "env") == 0)
		ms_env();
	else if (lms_strcmp(args[0], "exit") == 0)
		ms_exit(args, shell);
	else if (lms_strcmp(args[0], "export") == 0)
		ms_export(&(shell->env), args, &(shell->env_size));
	else if (lms_strcmp(args[0], "pwd") == 0)
		ms_pwd();
	else if (lms_strcmp(args[0], "unset") == 0)
		ms_unset(&(shell->env), args, &(shell->env_size));
	else
	{
		free(args);
		return (0);
	}
	free(args);
	return (1);
}
