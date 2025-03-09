/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgomes-p <vgomes-p@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 15:59:14 by vgomes-p          #+#    #+#             */
/*   Updated: 2025/03/08 20:38:07 by vgomes-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ms_redirs(t_minishell *shell, t_token *tokens, int **fd, int pos)
{
	t_token	*current;
	int		fd_in;
	int		fd_out;

	current = tokens;
	fd_in = -1;
	fd_out = -1;
	while (current && current->type != PIPE)
	{
		if (current->type == REDIR_IN && current->next)
		{
			fd_in = open(current->next->value, O_RDONLY);
			if (fd_in < 0)
			{
				file_errmsg(shell, current->next->value);
				exit(1);
			}
			dup2(fd_in, STDIN_FILENO);
			close(fd_in);
		}
		else if (current->type == REDIR_OUT && current->next)
		{
			fd_out = open(current->next->value, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (fd_out < 0)
			{
				file_errmsg(shell, current->next->value);
				exit(1);
			}
			dup2(fd_out, STDOUT_FILENO);
			close(fd_out);
		}
		else if (current->type == REDIR_APPEND && current->next)
		{
			fd_out = open(current->next->value, O_WRONLY | O_CREAT | O_APPEND, 0644);
			if (fd_out < 0)
			{
				file_errmsg(shell, current->next->value);
				exit(1);
			}
			dup2(fd_out, STDOUT_FILENO);
			close(fd_out);
		}
		else if (current->type == HEREDOC && current->next)
		{
			process_heredoc(shell, current);
		}
		current = current->next;
	}
	if (pos > 0)
		dup2(fd[pos - 1][0], STDIN_FILENO);
	if (fd[pos])
		dup2(fd[pos][1], STDOUT_FILENO);
}
