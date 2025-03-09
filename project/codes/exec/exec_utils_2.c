/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgomes-p <vgomes-p@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 13:57:11 by vgomes-p          #+#    #+#             */
/*   Updated: 2025/03/09 17:25:41 by vgomes-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static t_token	*handle_pipe_node(t_token **tokens, t_token *prev,
								t_token *current, t_token *cmd_start)
{
	t_token	*pipe_node;

	pipe_node = current;
	if (prev)
		prev->next = NULL;
	else
		cmd_start = NULL;
	*tokens = current->next;
	free(pipe_node->value);
	free(pipe_node);
	return (cmd_start);
}

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
		return (handle_pipe_node(tokens, prev, current, cmd_start));
	else
	{
		*tokens = NULL;
		return (cmd_start);
	}
}
