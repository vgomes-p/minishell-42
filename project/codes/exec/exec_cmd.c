/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgomes-p <vgomes-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 16:17:33 by vgomes-p          #+#    #+#             */
/*   Updated: 2025/02/05 17:01:50 by vgomes-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	**prepare_args(t_token *tokens)
{
	char	**args;
	int		arg_pos;
	t_token	*current;

	args = malloc(sizeof(char *) * (count_tokens(tokens) + 1));
	if (!args)
		return (NULL);
	current = tokens;
	arg_pos = 0;
	while (current)
	{
		args[arg_pos++] = current->value;
		current = current->next;
	}
	args[arg_pos] = NULL;
	return (args);
}

void	exec_extern(t_token *tokens, t_minishell *shell)
{
	char	**args;
	pid_t	pid;

	args = prepare_args(tokens);
	if (!args)
		return ;
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
		waitpid(pid, NULL, 0);
	free(args);
}

static char	**prepare_builtin_args(t_token *tokens)
{
	char	**args;
	t_token	*current;
	int		arg_pos;

	args = malloc(sizeof(char *) * (count_tokens(tokens) + 1));
	if (!args)
		return (NULL);
	current = tokens;
	arg_pos = 0;
	while (current)
	{
		args[arg_pos++] = current->value;
		current = current->next;
	}
	args[arg_pos] = NULL;
	return (args);
}

int	exec_builtin(t_token *tokens, t_minishell *shell)
{
	char	**args;
	int		ret;

	args = prepare_builtin_args(tokens);
	if (!args)
		return (-1);
	ret = 1;
	if (lms_strcmp(args[0], "cd") == 0)
		ms_cd(args);
	else if (lms_strcmp(args[0], "echo") == 0)
		ms_echo(args);
	else if (lms_strcmp(args[0], "env") == 0)
		ms_env();
	else if (lms_strcmp(args[0], "exit") == 0)
		ms_exit(args, shell);
	else if (lms_strcmp(args[0], "pwd") == 0)
		ms_pwd();
	else if (lms_strcmp(args[0], "export") == 0)
	{
		ms_export(shell, args, &shell->env);
		if (shell->error_code != 0)
			ret = shell->error_code;
	}
	else
		ret = 0;
	free(args);
	return (ret);
}
