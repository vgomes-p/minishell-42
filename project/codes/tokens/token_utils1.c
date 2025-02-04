/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgomes-p <vgomes-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 16:51:45 by vgomes-p          #+#    #+#             */
/*   Updated: 2025/02/04 16:54:08 by vgomes-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

bool	valid_syntax(t_token *tokens)
{
	t_token	*current;

	current = tokens;
	while (current)
	{
		if (current->type == PIPE || current->type == REDIR_OUT
			|| current->type == REDIR_IN || current->type == REDIR_APPEND
			|| current->type == HEREDOC)
		{
			if (!current->next || (current->next->type != ARG
					&& current->next->type != CMD))
			{
				printf(RED "Syntax error: '%s' operator without args.\n" RESET,
					current->value);
				return (false);
			}
		}
		current = current->next;
	}
	return (true);
}

void	cleanup_tokens(char **tokens, int token_cnt)
{
	int	index1;

	index1 = 0;
	while (index1 < token_cnt)
	{
		free(tokens[index1]);
		index1++;
	}
	free(tokens);
}
