/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_child.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgomes-p <vgomes-p@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 17:08:38 by vgomes-p          #+#    #+#             */
/*   Updated: 2025/03/09 17:08:38 by vgomes-p         ###   ########.fr       */
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

int	exec_parent(t_minishell *shell, int nb_pros, char **cmd, int **fd)
{
	if (!ft_strncmp(cmd[0], "./", 2) && is_dir(shell, cmd[0]) == 1)
		return (0);
	if (nb_pros == 1 && is_buildin(cmd[0]))
	{
		exec_builtin(shell->tokens, shell, fd, 0);
		sfree_int(fd);
		fd = NULL;
		return (0);
	}
	return (-1);
}

static void	exec_each_child(t_minishell *shell, t_exec *exec, int pos)
{
	t_token		*cmd_tokens;
	t_cmd_exec	cmd_exec;

	cmd_tokens = get_next_cmd(&exec->tokens_head);
	if (!cmd_tokens)
		return ;
	exec->cmd = prepare_args(cmd_tokens);
	if (!exec->cmd)
	{
		free_tokens(cmd_tokens);
		return ;
	}
	cmd_exec.cmd = exec->cmd;
	cmd_exec.fd = exec->fd;
	cmd_exec.pos = pos;
	cmd_exec.cmd_tokens = cmd_tokens;
	exec->pid[pos] = fork();
	if (exec->pid[pos] == 0)
		child(shell, &cmd_exec);
	free_matrix(&exec->cmd);
	free_tokens(cmd_tokens);
}

void	exec_child(t_minishell *shell, t_exec *exec, int pos)
{
	exec->pid = ft_calloc(exec->nbr_pros, sizeof(pid_t));
	if (!exec->pid)
		return ;
	pos = -1;
	while (++pos < exec->nbr_pros)
	{
		exec_each_child(shell, exec, pos);
	}
	cls_fd(exec->fd);
}

void	child(t_minishell *shell, t_cmd_exec *exec)
{
	if (!exec->cmd || *exec->cmd == NULL)
	{
		handle_invalid_file(shell);
		clean_child_res(shell, NULL, exec->fd, shell->error_code);
	}
	if (is_buildin(exec->cmd[0]))
		exec_builtin_in_child(shell, exec);
	else
	{
		ms_redirs(shell, exec->cmd_tokens, exec->fd, exec->pos);
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		cls_fd(exec->fd);
		exec_extern(exec->cmd, shell->env);
	}
	clean_child_res(shell, exec->cmd, exec->fd, shell->error_code);
}
