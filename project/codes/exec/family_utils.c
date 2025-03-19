/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   family_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgomes-p <vgomes-p@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 16:10:00 by vgomes-p          #+#    #+#             */
/*   Updated: 2025/03/19 16:10:00 by vgomes-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	exec_builtin_in_child(t_minishell *shell, t_cmd_exec *exec)
{
	ms_redirs(shell, exec->cmd_tokens, exec->fd, exec->pos);
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	cls_fd(exec->fd);
	if (lms_strcmp(exec->cmd[0], "cd") == 0)
		ms_cd(exec->cmd, shell);
	else if (lms_strcmp(exec->cmd[0], "echo") == 0)
		ms_echo(exec->cmd);
	else if (lms_strcmp(exec->cmd[0], "env") == 0)
		ms_env(shell);
	else if (lms_strcmp(exec->cmd[0], "exit") == 0)
		ms_exit(exec->cmd, shell);
	else if (lms_strcmp(exec->cmd[0], "pwd") == 0)
		ms_pwd(shell);
	else if (lms_strcmp(exec->cmd[0], "export") == 0)
		ms_export(shell, exec->cmd, &shell->env);
	else if (lms_strcmp(exec->cmd[0], "unset") == 0)
		ms_unset(shell, exec->cmd, &shell->env);
	exit(shell->exit_stt);
}
