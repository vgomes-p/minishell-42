/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgomes-p <vgomes-p@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 13:17:29 by vgomes-p          #+#    #+#             */
/*   Updated: 2025/03/09 17:27:22 by vgomes-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	open_heredoc_file(t_minishell *shell, int mode)
{
	int	fd;

	if (mode == 0)
		fd = open("__heredoc", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else
		fd = open("__heredoc", O_RDONLY);
	if (fd < 0)
	{
		perror(RED "heredoc" RESET);
		shell->error_code = 1;
		return (-1);
	}
	return (fd);
}

static void	write_heredoc_content(int fd, char *delimiter)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (!line || lms_strcmp(line, delimiter) == 0)
		{
			free(line);
			break ;
		}
		ft_putstr_fd(line, fd);
		ft_putstr_fd("\n", fd);
		free(line);
	}
}

static int	validate_heredoc_delimiter(t_minishell *shell, t_token *token)
{
	if (!token->next || !token->next->value)
	{
		ft_putstr_fd(RED "Syntax error: heredoc missing delimiter\n" RESET, 2);
		shell->error_code = 2;
		return (0);
	}
	return (1);
}

void	process_heredoc(t_minishell *shell, t_token *token)
{
	char	*delimiter;
	int		fd;

	if (!validate_heredoc_delimiter(shell, token))
		return ;
	delimiter = token->next->value;
	fd = open_heredoc_file(shell, 0);
	if (fd < 0)
		return ;
	write_heredoc_content(fd, delimiter);
	close(fd);
	fd = open_heredoc_file(shell, 1);
	if (fd < 0)
		return ;
	dup2(fd, STDIN_FILENO);
	close(fd);
}
