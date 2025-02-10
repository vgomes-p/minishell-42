/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils0.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgomes-p <vgomes-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 16:18:22 by vgomes-p          #+#    #+#             */
/*   Updated: 2025/02/10 17:55:39 by vgomes-p         ###   ########.fr       */
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

int	is_buildin(char *token)
{
	char	*buildin[8];
	int		pos;

	buildin[0] = "echo";
	buildin[1] = "cd";
	buildin[2] = "pwd";
	buildin[3] = "export";
	buildin[4] = "unset";
	buildin[5] = "env";
	buildin[6] = "exit";
	buildin[7] = NULL;
	pos = 0;
	while (buildin[pos])
	{
		if (ft_strncmp(token, buildin[pos], ft_strlen(buildin[pos])) == 0)
			return (1);
		pos++;
	}
	return (0);
}
