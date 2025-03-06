/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgomes-p <vgomes-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 15:59:14 by vgomes-p          #+#    #+#             */
/*   Updated: 2025/03/06 14:22:15 by vgomes-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	handle_redirects(t_token *token)
{
	int	fd;

	if (token->type == REDIR_IN)
	{
		fd = open(token->next->value, O_RDONLY);
		if (fd == -1)
		{
			perror("minishell");
			exit(1);
		}
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
	else if (token->type == REDIR_OUT)
	{
		fd = open(token->next->value, O_WRONLY | O_CREAT | O_TRUNC, 0664);
		if (fd == -1)
		{
			perror("minishell");
			exit(1);
		}
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
	else if (token->type == REDIR_APPEND)
	{
		fd = open(token->next->value, O_WRONLY | O_CREAT | O_APPEND, 0664);
		if (fd == -1)
		{
			perror("minishell");
			exit(1);
		}
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
}
