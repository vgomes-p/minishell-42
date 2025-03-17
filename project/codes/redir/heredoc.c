/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgomes-p <vgomes-p@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 13:17:29 by vgomes-p          #+#    #+#             */
/*   Updated: 2025/03/16 21:16:05 by vgomes-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	process_heredoc_line(int fd, char *line,
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

static int	write_heredoc_content(int fd, char *delimiter,
				t_minishell *shell, int quoted)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (!line)
			return (1);
		if (lms_strcmp(line, delimiter) == 0)
		{
			free(line);
			break ;
		}
		if (process_heredoc_line(fd, line, shell, quoted) == -1)
			return (1);
	}
	return (0);
}

static int	setup_heredoc(t_minishell *shell, char *delimiter, int quoted)
{
	int		fd;
	int		stts;
	void	(*old_sigquit)(int);

	old_sigquit = signal(SIGQUIT, SIG_IGN);
	fd = open_heredoc_file(shell, 0);
	if (fd < 0)
	{
		signal(SIGQUIT, old_sigquit);
		return (1);
	}
	stts = write_heredoc_content(fd, delimiter, shell, quoted);
	close(fd);
	signal(SIGQUIT, old_sigquit);
	if (stts == 1)
	{
		unlink("__heredoc");
		shell->cancelled_cmd = 1;
		return (1);
	}
	return (0);
}

int	process_heredoc(t_minishell *shell, t_token *token)
{
	char	*delimiter;
	char	*unquoted;
	int		quoted;
	int		fd;

	if (!validate_heredoc_delimiter(shell, token))
		return (1);
	delimiter = token->next->value;
	unquoted = unquote_delimiter(delimiter, &quoted);
	if (!unquoted)
		return (1);
	if (setup_heredoc(shell, unquoted, quoted) != 0)
	{
		free(unquoted);
		return (1);
	}
	free(unquoted);
	fd = open_heredoc_file(shell, 1);
	if (fd < 0)
		return (1);
	dup2(fd, STDIN_FILENO);
	close(fd);
	unlink("__heredoc");
	return (0);
}
