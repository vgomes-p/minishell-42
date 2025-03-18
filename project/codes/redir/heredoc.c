/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgomes-p <vgomes-p@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 13:17:29 by vgomes-p          #+#    #+#             */
/*   Updated: 2025/03/18 02:53:07 by vgomes-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	setup_signals_heredoc(void (**old_sigint)(int),
								void (**old_sigquit)(int))
{
	struct sigaction	sa;

	sa.sa_handler = heredoc_sigint_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	*old_sigint = signal(SIGINT, SIG_IGN);
	*old_sigquit = signal(SIGQUIT, SIG_IGN);
}

static int	process_heredoc_status(int stts, t_minishell *shell)
{
	if (WIFEXITED(stts))
	{
		if (WEXITSTATUS(stts) == 1)
		{
			unlink("__heredoc");
			shell->cancelled_cmd = 1;
			shell->exit_stt = 1;
			return (1);
		}
	}
	else if (WIFSIGNALED(stts))
	{
		if (WTERMSIG(stts) == SIGINT)
		{
			unlink("__heredoc");
			shell->cancelled_cmd = 1;
			shell->exit_stt = 130;
			return (1);
		}
	}
	return (0);
}

int	setup_heredoc(t_minishell *shell, char *delimiter, int quoted)
{
	int		fd;
	void	(*old_sigint)(int);
	void	(*old_sigquit)(int);
	pid_t	pid;
	int		stts;

	setup_signals_heredoc(&old_sigint, &old_sigquit);
	fd = open_heredoc_file(shell, 0);
	if (fd < 0)
	{
		signal(SIGINT, old_sigint);
		signal(SIGQUIT, old_sigquit);
		return (1);
	}
	pid = fork();
	if (pid == 0)
		handle_heredoc_child(fd, shell, delimiter, quoted);
	waitpid(pid, &stts, 0);
	close(fd);
	signal(SIGINT, old_sigint);
	signal(SIGQUIT, old_sigquit);
	return (process_heredoc_status(stts, shell));
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
