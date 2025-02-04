/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils0.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgomes-p <vgomes-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 16:18:22 by vgomes-p          #+#    #+#             */
/*   Updated: 2025/02/04 16:52:16 by vgomes-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	count_tokens(t_token *tokens)
{
	int		count;
	t_token	*current;

	count = 0;
	current = tokens;
	while (current)
	{
		count++;
		current = current->next;
	}
	return (count);
}

void	free_tokens(t_token *tokens)
{
	t_token	*current;
	t_token	*next;

	current = tokens;
	while (current)
	{
		next = current->next;
		if (current->value)
			free(current->value);
		free(current);
		current = next;
	}
}

bool	is_quotes(char ch)
{
	return (ch == '\'' || ch == '\"');
}

bool	is_operator(char *str)
{
	return (lms_strcmp(str, "|") == 0 || lms_strcmp(str, ">") == 0
		|| lms_strcmp(str, "<") == 0 || lms_strcmp(str, ">>") == 0
		|| lms_strcmp(str, "<<") == 0);
}
