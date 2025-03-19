/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_externs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgomes-p <vgomes-p@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 17:39:11 by vgomes-p          #+#    #+#             */
/*   Updated: 2025/03/19 16:57:28 by vgomes-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	allocate_pipes(t_exec *exec)
{
	int	pos;

	exec->fd = ft_calloc(exec->nbr_pros, sizeof(int *));
	if (!exec->fd)
		return (0);
	pos = -1;
	while (++pos < (exec->nbr_pros - 1))
	{
		exec->fd[pos] = ft_calloc(2, sizeof(int));
		if (!exec->fd[pos])
		{
			while (--pos >= 0)
				free(exec->fd[pos]);
			free(exec->fd);
			return (0);
		}
	}
	pos = -1;
	while (++pos < exec->nbr_pros - 1)
		pipe(exec->fd[pos]);
	return (1);
}

void	cleanup_processes(t_exec *exec, t_minishell *shell, int cmd_pos)
{
	int	pros_pos;

	(void)cmd_pos;
	cls_fd(exec->fd);
	pros_pos = -1;
	while (exec->fd[++pros_pos])
		exec->fd[pros_pos] = (int *) free_ptr((char *) exec->fd[pros_pos]);
	sfree_int(exec->fd);
	exec->fd = NULL;
	pros_pos = -1;
	while (++pros_pos < exec->nbr_pros)
		waitpid(exec->pid[pros_pos], &exec->stts, 0);
	if (!shell->cancelled_cmd)
	{
		if (WIFEXITED(exec->stts))
			shell->exit_stt = WEXITSTATUS(exec->stts);
		else if (WIFSIGNALED(exec->stts))
			shell->exit_stt = 128 + WTERMSIG(exec->stts);
	}
	shell->cancelled_cmd = 0;
	free(exec->pid);
}

static void	cleanup_execution(t_exec *exec, t_minishell *shell,
							int cmd_pos, t_token *tokens_copy)
{
	int	ind;

	if (cmd_pos != 0)
	{
		exec_child(shell, exec, cmd_pos);
		cleanup_processes(exec, shell, cmd_pos);
		ind = 0;
		while (ind < exec->nbr_pros)
		{
			if (exec->cmd_tokens[ind])
				free_tokens(exec->cmd_tokens[ind]);
			ind++;
		}
	}
	free(exec->cmd_tokens);
	free_matrix(&exec->cmd);
	if (cmd_pos == 0)
		free_tokens(tokens_copy);
}

void	free_exec_resources(t_exec *exec, t_token *tokens_copy)
{
	int	ind;

	free_matrix(&exec->cmd);
	if (exec->fd)
	{
		ind = 0;
		while (ind < exec->nbr_pros - 1)
		{
			if (exec->fd[ind])
				free(exec->fd[ind]);
			ind++;
		}
		free(exec->fd);
	}
	if (exec->cmd_tokens)
		free(exec->cmd_tokens);
	free_tokens(tokens_copy);
}

void	exec_cmd(t_minishell *shell)
{
	int		cmd_pos;
	t_exec	exec;
	t_token	*tokens_copy;

	if (!shell->tokens || !shell->tokens->value || !*shell->tokens->value)
		return ;
	tokens_copy = cpy_token_ls(shell->tokens);
	if (!tokens_copy)
		return ;
	exec = init_exec(shell, tokens_copy);
	if (!exec.fd || !exec.cmd || !exec.cmd_tokens)
	{
		free_exec_resources(&exec, tokens_copy);
		return ;
	}
	cmd_pos = exec_parent(shell, exec.nbr_pros, exec.cmd, exec.fd);
	free_matrix(&exec.cmd);
	cleanup_execution(&exec, shell, cmd_pos, tokens_copy);
}
