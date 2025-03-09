/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils_0.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgomes-p <vgomes-p@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 17:41:12 by vgomes-p          #+#    #+#             */
/*   Updated: 2025/03/08 21:38:18 by vgomes-p         ###   ########.fr       */
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

char	**prepare_args(t_token *tokens)
{
	char	**args;
	int		arg_count;
	int		arg_pos;
	t_token *current;

	arg_count = 0;
	arg_pos = 0;
	if (!tokens)
		return (NULL);

	current = tokens;
	while (current)
	{
		if (current->type == CMD || current->type == ARG)
			arg_count++;
		// Pular o próximo token se for um redirecionamento
		if (current->type == REDIR_IN || current->type == REDIR_OUT ||
			current->type == REDIR_APPEND || current->type == HEREDOC)
			current = current->next; // Pular o valor do redirecionamento
		if (current)
			current = current->next;
	}
	args = malloc(sizeof(char *) * (arg_count + 1));
	if (!args)
		return (NULL);
	current = tokens;
	while (current && arg_pos < arg_count)
	{
		if (current->type == CMD || current->type == ARG)
		{
			args[arg_pos] = ft_strdup(current->value);
			if (!args[arg_pos])
			{
				free_matrix(&args);
				return (NULL);
			}
			arg_pos++;
		}
		if (current->type == REDIR_IN || current->type == REDIR_OUT ||
			current->type == REDIR_APPEND || current->type == HEREDOC)
			current = current->next;
		if (current)
			current = current->next;
	}
	args[arg_pos] = NULL;
	return (args);
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

void	cls_fd(int **fd)
{
	int	pos;

	pos = 0;
	while (fd[pos])
	{
		close(fd[pos][0]);
		close(fd[pos][1]);
		pos++;
	}
}
