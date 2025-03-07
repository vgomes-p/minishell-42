/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgomes-p <vgomes-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 13:57:11 by vgomes-p          #+#    #+#             */
/*   Updated: 2025/02/21 14:22:02 by vgomes-p         ###   ########.fr       */
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
