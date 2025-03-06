/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_child.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgomes-p <vgomes-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 14:14:21 by vgomes-p          #+#    #+#             */
/*   Updated: 2025/03/06 17:39:40 by vgomes-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	process_redirections(t_token *current)
{
	while (current)
	{
		if (current->type == REDIR_IN || current->type == REDIR_OUT || 
			current->type == REDIR_APPEND)
			handle_redirects(current);
		else if (current->type == HEREDOC)
			handle_heredoc(current);
		current = current->next;
	}
}

static int	allocate_pid_memory(t_exec *exec)
{
	exec->pid = malloc(sizeof(pid_t) * exec->nbr_pros);
	if (!exec->pid)
		return (0);
	return (1);
}

static void	execute_command(t_minishell *shell, t_exec *exec, 
							t_token *cmd_tokens, int pos)
{
	exec->cmd = tokens_matrix(cmd_tokens);
	exec->pid[pos] = fork();
	if (exec->pid[pos] == 0)
	{
		child(shell, exec->cmd, exec->fd, pos);
	}
	sfree(exec->cmd);
	exec->cmd = NULL;
	free_tokens(cmd_tokens);
}

static void	process_commands(t_minishell *shell, t_exec *exec, 
							t_token **current_tokens)
{
	int		pos;
	t_token	*cmd_tokens;

	pos = -1;
	while (++pos < exec->nbr_pros)
	{
		cmd_tokens = get_next_cmd(current_tokens);
		execute_command(shell, exec, cmd_tokens, pos);
	}
}

void	exec_child(t_minishell *shell, t_exec *exec, int pos)
{
	t_token	*current_tokens;

	(void)pos;
	process_redirections(exec->temp);
	if (!allocate_pid_memory(exec))
		return ;
	current_tokens = shell->tokens;
	process_commands(shell, exec, &current_tokens);
}
