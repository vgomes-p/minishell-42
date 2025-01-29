/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token0.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgomes-p <vgomes-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 17:10:12 by vgomes-p          #+#    #+#             */
/*   Updated: 2025/01/28 17:50:46 by vgomes-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static t_token	*mktoken(char *value, t_token_tp type)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->value = ft_strdup(value);
	token->type = type;
	token->next = NULL;
	return (token);
}

static bool	is_operator(char *str)
{
	return (lms_strcmp(str, "|") == 0 || lms_strcmp(str, ">") == 0
		|| lms_strcmp(str, "<") == 0 || lms_strcmp(str, ">>") == 0
		|| lms_strcmp(str, "<<") == 0);
}

t_token_tp	get_token_type(char *token, t_token *current, int is_first)
{
	t_token_tp	type;

	type = ARG;
	if (is_operator(token))
	{
		if (lms_strcmp(token, "|") == 0)
			type = PIPE;
		else if (lms_strcmp(token, ">") == 0)
			type = REDIR_OUT;
		else if (lms_strcmp(token, ">>") == 0)
			type = REDIR_APPEND;
		else if (lms_strcmp(token, "<") == 0)
			type = REDIR_IN;
		else if (lms_strcmp(token, "<<") == 0)
			type = HEREDOC;
	}
	else if (is_first || (current && current->type == PIPE))
		type = CMD;
	return (type);
}

t_token	*tokening(char *input)
{
	char	**split;
	t_token	*head;
	t_token	*current;
	t_token	*nwtoken;
	int		index;

	split = ft_split(input, ' ');
	head = NULL;
	current = NULL;
	index = 0;
	while (split[index])
	{
		nwtoken = mktoken(split[index],
				get_token_type(split[index], current, index == 0));
		if (!nwtoken)
			return (NULL);
		if (!head)
			head = nwtoken;
		else
			current->next = nwtoken;
		current = nwtoken;
		index++;
	}
	return (head);
}

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
