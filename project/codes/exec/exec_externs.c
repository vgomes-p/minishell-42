/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_externs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgomes-p <vgomes-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 17:39:11 by vgomes-p          #+#    #+#             */
/*   Updated: 2025/03/06 14:14:41 by vgomes-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_exec	init_exec(t_minishell *shell)
{
	int		pos;
	t_exec	exec;

	exec.pid = 0;
	exec.stts = 0;
	exec.nbr_pros = 1;
	exec.temp = shell->tokens;
	exec.cmd = tokens_matrix(exec.temp);
	while (exec.temp)
	{
		if (exec.temp->type == PIPE)
			exec.nbr_pros++;
		exec.temp = exec.temp->next;
	}
	exec.fd = ft_calloc(exec.nbr_pros, sizeof(int *));
	pos = -1;
	while (++pos < (exec.nbr_pros - 1))
		exec.fd[pos] = ft_calloc(2, sizeof(int));
	pos = -1;
	while (++pos < exec.nbr_pros - 1)
		pipe(exec.fd[pos]);
	exec.temp = shell->tokens;
	return (exec);
}

int	exec_parent(t_minishell *shell, int nb_pros, char **cmd, int **fd)
{
	if (!ft_strncmp(cmd[0], "./", 2) && is_dir(shell, cmd[0]) == 1)
		return (0);
	if (nb_pros > 1)
		return (-1);
	if (exec_builtin(shell->tokens, shell))
	{
		sfree_int(fd);
		fd = NULL;
		return (0);
	}
	return (-1);
}

void	cleanup_processes(t_exec *exec, t_minishell *shell, int cmd_pos)
{
	int	pros_pos;

	cls_fd(exec->fd);
	pros_pos = -1;
	while (exec->fd[++pros_pos])
		exec->fd[pros_pos] = (int *) free_ptr((char *) exec->fd[pros_pos]);
	sfree_int(exec->fd);
	exec->fd = NULL;
	pros_pos = -1;
	while (++pros_pos < exec->nbr_pros)
		waitpid(exec->pid[pros_pos], &exec->stts, 0);
	if (WIFEXITED(exec->stts) && cmd_pos != exec->nbr_pros)
		shell->error_code = WEXITSTATUS(exec->stts);
	free(exec->pid);
}

void	exec_cmd(t_minishell *shell)
{
	int		cmd_pos;
	t_exec	exec;
	t_token	*tokens_copy;

	if (!shell->tokens || !shell->tokens->value || !*shell->tokens->value)
		return ;
	tokens_copy = cpy_token_ls(shell->tokens);
	exec = init_exec(shell);
	cmd_pos = exec_parent(shell, exec.nbr_pros, exec.cmd, exec.fd);
	if (cmd_pos > 0)
	{
		sfree(exec.cmd);
		exec.cmd = NULL;
	}
	if (cmd_pos == 0)
		return ;
	exec_child(shell, &exec, cmd_pos);
	cleanup_processes(&exec, shell, cmd_pos);
	free_tokens(tokens_copy);
}
