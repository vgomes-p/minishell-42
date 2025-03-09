/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_externs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgomes-p <vgomes-p@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 17:39:11 by vgomes-p          #+#    #+#             */
/*   Updated: 2025/03/08 21:29:48 by vgomes-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_exec	init_exec(t_minishell *shell, t_token *tokens)
{
	t_exec	exec;
	int		pos;

	(void)shell;
	exec.tokens_head = tokens;
	exec.temp = tokens;
	exec.pid = NULL;
	exec.stts = 0;
	exec.nbr_pros = 1;
	exec.cmd = tokens_matrix(exec.temp);
	while (exec.temp)
	{
		if (exec.temp->type == PIPE)
			exec.nbr_pros++;
		exec.temp = exec.temp->next;
	}
	if (exec.nbr_pros <= 0)
	{
		free_matrix(&exec.cmd);
		exec.fd = NULL;
		return (exec);
	}
	exec.fd = ft_calloc(exec.nbr_pros, sizeof(int *));
	if (!exec.fd)
	{
		free_matrix(&exec.cmd);
		return (exec);
	}
	pos = -1;
	while (++pos < (exec.nbr_pros - 1))
	{
		exec.fd[pos] = ft_calloc(2, sizeof(int));
		if (!exec.fd[pos])
		{
			while (--pos >= 0)
				free(exec.fd[pos]);
			free(exec.fd);
			free_matrix(&exec.cmd);
			return (exec);
		}
	}
	pos = -1;
	while (++pos < exec.nbr_pros - 1)
		pipe(exec.fd[pos]);
	exec.temp = exec.tokens_head;
	return (exec);
}

int	exec_parent(t_minishell *shell, int nb_pros, char **cmd, int **fd)
{
	if (!ft_strncmp(cmd[0], "./", 2) && is_dir(shell, cmd[0]) == 1)
		return (0);
	if (nb_pros > 1)
		return (-1);
	if (is_buildin(cmd[0]))
	{
		exec_builtin(shell->tokens, shell, fd, 0);
		sfree_int(fd);
		fd = NULL;
		return (0);
	}
	return (-1);
}

void	exec_child(t_minishell *shell, t_exec *exec, int pos)
{
	t_token *cmd_tokens;
	t_token *current_tokens;

	exec->pid = ft_calloc(exec->nbr_pros, sizeof(pid_t));
	if (!exec->pid)
		return ;
	current_tokens = exec->tokens_head;
	pos = -1;
	while (++pos < exec->nbr_pros)
	{
		cmd_tokens = get_next_cmd(&current_tokens);
		exec->cmd = tokens_matrix(cmd_tokens);
		if (is_buildin(exec->cmd[0]))
		{
			exec_builtin(cmd_tokens, shell, exec->fd, 0);
			free_matrix(&exec->cmd);
			free_tokens(cmd_tokens);
			continue ;
		}
		exec->pid[pos] = fork();
		if (exec->pid[pos] == 0)
			child(shell, exec->cmd, exec->fd, pos);
		free_matrix(&exec->cmd);
		free_tokens(cmd_tokens);
	}
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
	if (WIFEXITED(exec->stts))
		shell->exit_stt = WEXITSTATUS(exec->stts); // Atualizar exit_stt
	else if (WIFSIGNALED(exec->stts))
		shell->exit_stt = 128 + WTERMSIG(exec->stts); // Para sinais como SIGINT
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
	exec = init_exec(shell, tokens_copy);
	if (!exec.fd)
	{
		free_matrix(&exec.cmd);
		free_tokens(tokens_copy);
		return ;
	}
	if (is_buildin(exec.cmd[0]))
	{
		exec_builtin(shell->tokens, shell, exec.fd, 0);
		free_matrix(&exec.cmd);
		sfree_int(exec.fd);
		free_tokens(tokens_copy);
		return;
	}
	cmd_pos = exec_parent(shell, exec.nbr_pros, exec.cmd, exec.fd);
	if (cmd_pos > 0)
		free_matrix(&exec.cmd);
	if (cmd_pos == 0)
	{
		free_matrix(&exec.cmd);
		sfree_int(exec.fd);
		free_tokens(tokens_copy);
		return;
	}
	exec_child(shell, &exec, cmd_pos);
	cleanup_processes(&exec, shell, cmd_pos);
	free_matrix(&exec.cmd);
	sfree_int(exec.fd);
	free(exec.pid);
	free_tokens(tokens_copy);
}

