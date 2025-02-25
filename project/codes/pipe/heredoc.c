/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sthrodri <sthrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 13:17:29 by vgomes-p          #+#    #+#             */
/*   Updated: 2025/02/25 17:12:43 by sthrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*expand(t_minishell *shell, char *input, char **envp)
{
	(void) shell;
	(void) envp;
	return (ft_strdup(input));
}

int	heredoc(t_minishell *shell, const char *eof, char **envp)
{
	char	*input;
	int		file;

	input = NULL;
	unlink("__heredoc");
	file = open("__heredoc", O_WRONLY | O_CREAT | O_TRUNC, 0600);
	if (file < 0)
		return (-1);
	while (1)
	{
		input = readline("> ");
		if (!input || ft_strncmp(eof, input, ft_strlen(eof) + 1) == 0)
		{
			sfree(&input);
			break ;
		}
		if (*eof != '\'' && *eof != '\"' && ft_strchr(input, '$'))
			input = expand(shell, input, envp);
		write(file, input, ft_strlen(input));
		write(file, "\n", 1);
		sfree(&input);
	}
	close(file);
	return (open("__heredoc", O_RDONLY));
}
