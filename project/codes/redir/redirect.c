/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgomes-p <vgomes-p@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 15:59:14 by vgomes-p          #+#    #+#             */
/*   Updated: 2025/03/09 17:30:24 by vgomes-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	handle_redir_in(t_minishell *shell, t_token *current)
{
	int	fd_in;

	fd_in = open(current->next->value, O_RDONLY);
	if (fd_in < 0)
	{
		file_errmsg(shell, current->next->value);
		exit(1);
	}
	dup2(fd_in, STDIN_FILENO);
	close(fd_in);
}

static void	handle_redir_out(t_minishell *shell, t_token *current, int append)
{
	int	fd_out;
	int	flags;

	flags = O_WRONLY | O_CREAT;
	if (append)
		flags |= O_APPEND;
	else
		flags |= O_TRUNC;
	fd_out = open(current->next->value, flags, 0644);
	if (fd_out < 0)
	{
		file_errmsg(shell, current->next->value);
		exit(1);
	}
	dup2(fd_out, STDOUT_FILENO);
	close(fd_out);
}

static void	pros_redirs(t_minishell *shell, t_token *current)
{
	if (current->type == REDIR_IN && current->next)
		handle_redir_in(shell, current);
	else if (current->type == REDIR_OUT && current->next)
		handle_redir_out(shell, current, 0);
	else if (current->type == REDIR_APPEND && current->next)
		handle_redir_out(shell, current, 1);
	else if (current->type == HEREDOC && current->next)
		process_heredoc(shell, current);
}

void	ms_redirs(t_minishell *shell, t_token *tokens, int **fd, int pos)
{
	t_token	*current;

	current = tokens;
	while (current && current->type != PIPE)
	{
		if ((current->type == REDIR_IN || current->type == REDIR_OUT
				|| current->type == REDIR_APPEND || current->type == HEREDOC)
			&& current->next)
			pros_redirs(shell, current);
		current = current->next;
	}
	if (pos > 0)
		dup2(fd[pos - 1][0], STDIN_FILENO);
	if (fd[pos])
		dup2(fd[pos][1], STDOUT_FILENO);
}
