/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgomes-p <vgomes-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 15:59:14 by vgomes-p          #+#    #+#             */
/*   Updated: 2025/03/06 15:12:53 by vgomes-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	open_input_file(char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		perror("minishell");
		exit(1);
	}
	return (fd);
}

static int	open_output_file(char *filename)
{
	int	fd;

	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0664);
	if (fd == -1)
	{
		perror("minishell");
		exit(1);
	}
	return (fd);
}

static int	open_append_file(char *filename)
{
	int	fd;

	fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0664);
	if (fd == -1)
	{
		perror("minishell");
		exit(1);
	}
	return (fd);
}

static void	redirect_and_close(int fd, int target_fd)
{
	dup2(fd, target_fd);
	close(fd);
}

void	handle_redirects(t_token *token)
{
	int	fd;

	if (token->type == REDIR_IN)
	{
		fd = open_input_file(token->next->value);
		redirect_and_close(fd, STDIN_FILENO);
	}
	else if (token->type == REDIR_OUT)
	{
		fd = open_output_file(token->next->value);
		redirect_and_close(fd, STDOUT_FILENO);
	}
	else if (token->type == REDIR_APPEND)
	{
		fd = open_append_file(token->next->value);
		redirect_and_close(fd, STDOUT_FILENO);
	}
}
