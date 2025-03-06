/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_child.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgomes-p <vgomes-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 14:14:21 by vgomes-p          #+#    #+#             */
/*   Updated: 2025/03/06 14:23:51 by vgomes-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	exec_child(t_minishell *shell, t_exec *exec, int pos)
{
	t_token	*cmd_tokens;
	t_token	*current_tokens;
	t_token	*current;

	current = exec->temp;
	while (current)
	{
		if (current->type == REDIR_IN || current->type == REDIR_OUT || current->type == REDIR_APPEND)
			handle_redirects(current);
		else if (current->type == HEREDOC)
			handle_heredoc(current);
		current = current->next;
	}
	exec->pid = malloc(sizeof(pid_t) * exec->nbr_pros);
	if (!exec->pid)
		return ;
	current_tokens = shell->tokens;
	pos = -1;
	while (++pos < exec->nbr_pros)
	{
		cmd_tokens = get_next_cmd(&current_tokens);
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
}
