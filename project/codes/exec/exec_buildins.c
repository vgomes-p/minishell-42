/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_buildins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgomes-p <vgomes-p@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 16:17:33 by vgomes-p          #+#    #+#             */
/*   Updated: 2025/03/16 19:00:32 by vgomes-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	restore_std_fds(int stdin_backup, int stdout_backup)
{
	dup2(stdin_backup, STDIN_FILENO);
	dup2(stdout_backup, STDOUT_FILENO);
	close(stdin_backup);
	close(stdout_backup);
}

static int	handle_builtin_command(char **args, t_minishell *shell)
{
	int	ret;

	ret = 1;
	if (lms_strcmp(args[0], "cd") == 0)
	{
		ms_cd(args, shell);
		shell->exit_stt = shell->error_code;
	}
	else if (lms_strcmp(args[0], "echo") == 0)
	{
		ms_echo(args);
		shell->exit_stt = 0;
	}
	else if (lms_strcmp(args[0], "env") == 0)
	{
		ms_env(shell);
		shell->exit_stt = 0;
	}
	else if (lms_strcmp(args[0], "exit") == 0)
		ms_exit(args, shell);
	return (ret);
}

static int	handle_more_builtins(char **args, t_minishell *shell)
{
	int	ret;

	ret = 1;
	if (lms_strcmp(args[0], "pwd") == 0)
	{
		ms_pwd(shell);
		shell->exit_stt = shell->error_code;
	}
	else if (lms_strcmp(args[0], "export") == 0)
	{
		ms_export(shell, args, &shell->env);
		ret = shell->error_code;
		shell->exit_stt = ret;
	}
	else if (lms_strcmp(args[0], "unset") == 0)
	{
		ms_unset(shell, args, &shell->env);
		shell->exit_stt = shell->error_code;
	}
	else
		ret = 0;
	return (ret);
}

static char	**prepare_builtin(t_token *tokens, t_minishell *shell,
				int **fd, int pos)
{
	char	**args;
	int		stdin_backup;
	int		stdout_backup;

	stdin_backup = dup(STDIN_FILENO);
	stdout_backup = dup(STDOUT_FILENO);
	if (ms_redirs(shell, tokens, fd, pos) != 0)
	{
		restore_std_fds(stdin_backup, stdout_backup);
		return (NULL);
	}
	args = prepare_args(tokens);
	if (!args)
	{
		restore_std_fds(stdin_backup, stdout_backup);
		return (NULL);
	}
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	return (args);
}

int	exec_builtin(t_token *tokens, t_minishell *shell, int **fd, int pos)
{
	char	**args;
	int		ret;
	int		stdin_backup;
	int		stdout_backup;

	stdin_backup = dup(STDIN_FILENO);
	stdout_backup = dup(STDOUT_FILENO);
	args = prepare_builtin(tokens, shell, fd, pos);
	if (!args)
		return (-1);
	if (lms_strcmp(args[0], "cd") == 0 || lms_strcmp(args[0], "echo") == 0
		|| lms_strcmp(args[0], "env") == 0 || lms_strcmp(args[0], "exit") == 0)
		ret = handle_builtin_command(args, shell);
	else
		ret = handle_more_builtins(args, shell);
	restore_std_fds(stdin_backup, stdout_backup);
	free_matrix(&args);
	return (ret);
}
