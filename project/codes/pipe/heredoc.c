/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgomes-p <vgomes-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 13:17:29 by vgomes-p          #+#    #+#             */
/*   Updated: 2025/02/21 13:17:39 by vgomes-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char *expand(t_minishell *ms, char *input, char **envp)
{

	(void) ms;
	(void) envp;
	return ft_strdup(input);
}

int	heredoc(t_minishell *ms, const char *eof, char **envp)
{
	char	*input;
	int		file;

	input = NULL;
	unlink("__heredoc"); // Remove o arquivo se já existir
	file = open("__heredoc", O_WRONLY | O_CREAT | O_TRUNC, 0600);
	if (file < 0)
		return (-1);
	while (1)
	{
		input = readline("> ");
		if (!input || ft_strncmp(eof, input, ft_strlen(eof) + 1) == 0)
		{
			sfree(&input);
			break;
		}
		if (*eof != '\'' && *eof != '\"' && ft_strchr(input, '$'))
			input = expand(ms, input, envp); // Certifique-se de que expand retorna um char*
		write(file, input, ft_strlen(input));
		write(file, "\n", 1);
		sfree(&input);
	}
	close(file);
	return (open("__heredoc", O_RDONLY));
}

