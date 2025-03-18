/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgomes-p <vgomes-p@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 20:34:58 by vgomes-p          #+#    #+#             */
/*   Updated: 2025/03/16 20:34:58 by vgomes-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	heredoc_sigint_handler(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\n", 1);
	exit(130);
}

char	*unquote_delimiter(char *delimiter, int *quoted)
{
	size_t	len;

	len = ft_strlen(delimiter);
	if (len >= 2 && ((delimiter[0] == '\'' && delimiter[len - 1] == '\'')
			|| (delimiter[0] == '"' && delimiter[len - 1] == '"')))
	{
		*quoted = 1;
		return (ft_substr(delimiter, 1, len - 2));
	}
	*quoted = 0;
	return (ft_strdup(delimiter));
}

int	open_heredoc_file(t_minishell *shell, int mode)
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

int	validate_heredoc_delimiter(t_minishell *shell, t_token *token)
{
	if (!token->next || !token->next->value)
	{
		ft_putstr_fd(RED "Syntax error: heredoc missing delimiter\n" RESET, 2);
		shell->error_code = 2;
		return (0);
	}
	return (1);
}

void	heredoc_warning(char *delimiter)
{
	ft_putstr_fd(YELLOW "warning: heredoc delimited by end-of-file (wanted '",
		2);
	ft_putstr_fd(delimiter, 2);
	ft_putstr_fd("')\n" RESET, 2);
}
