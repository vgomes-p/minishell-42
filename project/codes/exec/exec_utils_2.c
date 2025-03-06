/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgomes-p <vgomes-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 13:57:11 by vgomes-p          #+#    #+#             */
/*   Updated: 2025/03/06 17:14:27 by vgomes-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_token	*get_next_cmd(t_token **tokens)
{
	t_token	*current;
	t_token	*cmd_start;
	t_token	*prev;

	if (!tokens || !*tokens)
		return (NULL);
	cmd_start = *tokens;
	current = *tokens;
	prev = NULL;
	while (current && current->type != PIPE)
	{
		prev = current;
		current = current->next;
	}
	if (current)
	{
		if (prev)
			prev->next = NULL;
		*tokens = current->next;
	}
	else
		*tokens = NULL;
	return (cmd_start);
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

void	file_errmsg(t_minishell *shell, char *cmd)
{
	char	*color_cmd;

	color_cmd = ft_strjoin(RED, cmd);
	ft_putstr_fd(color_cmd, 2);
	free(color_cmd);
	shell->error_code = 1;
}
