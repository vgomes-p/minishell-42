/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgomes-p <vgomes-p@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 02:12:12 by vgomes-p          #+#    #+#             */
/*   Updated: 2025/03/18 02:12:12 by vgomes-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	process_heredoc_line(int fd, char *line,
		t_minishell *shell, int quoted)
{
	char	*expanded_ln;

	if (quoted)
	{
		ft_putstr_fd(line, fd);
		free(line);
	}
	else
	{
		expanded_ln = expand_inside(shell, line);
		if (!expanded_ln)
			return (-1);
		ft_putstr_fd(expanded_ln, fd);
		free(expanded_ln);
	}
	ft_putstr_fd("\n", fd);
	return (0);
}

int	write_heredoc_content(int fd, char *delimiter,
		t_minishell *shell, int quoted)
{
	char	*line;
	int		line_cnt;

	line_cnt = 0;
	while (1)
	{
		line = readline("miniheredoc> ");
		if (!line)
		{
			heredoc_warning(delimiter);
			if (line_cnt == 0)
				return (1);
			break ;
		}
		if (lms_strcmp(line, delimiter) == 0)
		{
			free(line);
			break ;
		}
		if (process_heredoc_line(fd, line, shell, quoted) == -1)
			return (1);
		line_cnt++;
	}
	return (0);
}

int	handle_heredoc_child(int fd, t_minishell *shell,
		char *delimiter, int quoted)
{
	struct sigaction	sa;
	int					stts;

	sa.sa_handler = heredoc_sigint_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
	stts = write_heredoc_content(fd, delimiter, shell, quoted);
	close(fd);
	if (stts == 0)
		exit(0);
	else
		exit(1);
}
