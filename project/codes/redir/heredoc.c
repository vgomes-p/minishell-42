/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgomes-p <vgomes-p@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 13:17:29 by vgomes-p          #+#    #+#             */
/*   Updated: 2025/03/08 20:50:39 by vgomes-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	process_heredoc(t_minishell *shell, t_token *token)
{
	char	*delimiter;
	char	*line;
	int		fd;

	if (!token->next || !token->next->value)
	{
		ft_putstr_fd(RED "Syntax error: heredoc missing delimiter\n" RESET, 2);
		shell->error_code = 2;
		return;
	}
	delimiter = token->next->value;
	fd = open("__heredoc", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
	{
		perror(RED "heredoc" RESET);
		shell->error_code = 1;
		return;
	}
	while (1)
	{
		line = readline("> ");
		if (!line || lms_strcmp(line, delimiter) == 0)
		{
			free(line);
			break;
		}
		ft_putstr_fd(line, fd);
		ft_putstr_fd("\n", fd);
		free(line);
	}
	close(fd);
	fd = open("__heredoc", O_RDONLY);
	if (fd < 0)
	{
		perror(RED "heredoc" RESET);
		shell->error_code = 1;
		return;
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
}