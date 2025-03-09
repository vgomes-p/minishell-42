/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgomes-p <vgomes-p@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 17:16:36 by vgomes-p          #+#    #+#             */
/*   Updated: 2025/03/09 17:16:36 by vgomes-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_buildin(char *token)
{
	char	**ls;
	int		pos;

	ls = ft_calloc(8, sizeof(char *));
	if (!ls)
		return (-1);
	ls[0] = ft_strdup("echo");
	ls[1] = ft_strdup("cd");
	ls[2] = ft_strdup("pwd");
	ls[3] = ft_strdup("export");
	ls[4] = ft_strdup("unset");
	ls[5] = ft_strdup("env");
	ls[6] = ft_strdup("exit");
	ls[7] = NULL;
	pos = -1;
	while (ls[++pos])
	{
		if (!ft_strncmp(token, ls[pos], ft_strlen(token)))
		{
			free_matrix(&ls);
			return (1);
		}
	}
	free_matrix(&ls);
	return (0);
}

int	is_redir(t_token *token)
{
	return (token->type == REDIR_IN || token->type == REDIR_OUT
		|| token->type == REDIR_APPEND || token->type == HEREDOC);
}

int	is_dir(t_minishell *shell, char *cmd)
{
	struct stat	file_info;

	(void)shell;
	if (stat(cmd, &file_info) != 0)
		return (-1);
	if (S_ISDIR(file_info.st_mode))
	{
		ft_putstr_fd(RED, 2);
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": is a directory\n" RESET, 2);
		shell->error_code = 126;
		return (1);
	}
	return (0);
}
