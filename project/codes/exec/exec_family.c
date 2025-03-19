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

static void	prepare_cmd_tokens(t_exec *exec)
{
	int	ind;

	ind = 0;
	while (ind < exec->nbr_pros)
	{
		exec->cmd_tokens[ind] = get_next_cmd(&exec->tokens_head);
		if (!exec->cmd_tokens[ind])
			break ;
		ind++;
	}
	exec->pid = ft_calloc(exec->nbr_pros, sizeof(pid_t));
}

static void	util_exec_child(t_minishell *shell, t_exec *exec, int ind)
{
	t_cmd_exec	cmd_exec;

	exec->cmd = prepare_args(exec->cmd_tokens[ind]);
	if (!exec->cmd)
		return ;
	cmd_exec = (t_cmd_exec){exec->cmd, exec->fd, ind, exec->cmd_tokens[ind]};
	exec->pid[ind] = fork();
	if (exec->pid[ind] == 0)
	{
		child(shell, &cmd_exec);
		free_matrix(&exec->cmd);
		exit(shell->exit_stt);
	}
	free_matrix(&exec->cmd);
}

void	exec_child(t_minishell *shell, t_exec *exec, int pos)
{
	int	ind;

	(void)pos;
	prepare_cmd_tokens(exec);
	if (!exec->pid)
		return ;
	ind = 0;
	while (ind < exec->nbr_pros)
	{
		if (!exec->cmd_tokens[ind])
		{
			ind++;
			continue ;
		}
		util_exec_child(shell, exec, ind);
		ind++;
	}
	cls_fd(exec->fd);
}

void	child(t_minishell *shell, t_cmd_exec *exec)
{
	if (ms_redirs(shell, exec->cmd_tokens, exec->fd, exec->pos) != 0)
		clean_child_res(shell, exec->cmd, exec->fd, 1);
	if (!exec->cmd || *exec->cmd == NULL)
	{
		handle_invalid_file(shell);
		clean_child_res(shell, exec->cmd, exec->fd, shell->error_code);
	}
	if (is_buildin(exec->cmd[0]))
		exec_builtin_in_child(shell, exec);
	else
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		cls_fd(exec->fd);
		exec_extern(exec->cmd, shell->env);
	}
	clean_child_res(shell, exec->cmd, exec->fd, shell->error_code);
}
