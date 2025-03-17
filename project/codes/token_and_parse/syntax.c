/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgomes-p <vgomes-p@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 17:56:44 by vgomes-p          #+#    #+#             */
/*   Updated: 2025/03/14 17:56:44 by vgomes-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static bool	is_pipe_valid(t_token *current, bool cmd_before)
{
	if (!cmd_before)
	{
		printf(RED "Syntax error: unexpected token\n" RESET);
		return (false);
	}
	if (!current->next || (current->next->type != CMD
			&& current->next->type != ARG))
	{
		printf(RED "Syntax error: unexpected token\n" RESET);
		return (false);
	}
	return (true);
}

static bool	is_redir_valid(t_token *current)
{
	if (!current->next || current->next->type != ARG)
	{
		printf(RED "Syntax error: '%s' operator without args.\n" RESET,
			current->value);
		return (false);
	}
	return (true);
}

static bool	process_token(t_token **current, bool *cmd_before)
{
	if ((*current)->type == CMD || (*current)->type == ARG)
		*cmd_before = true;
	else if ((*current)->type == PIPE)
	{
		if (!is_pipe_valid(*current, *cmd_before))
			return (false);
		*cmd_before = false;
	}
	else if ((*current)->type == REDIR_OUT || (*current)->type == REDIR_IN
		|| (*current)->type == REDIR_APPEND || (*current)->type == HEREDOC)
	{
		if (!is_redir_valid(*current))
			return (false);
		*current = (*current)->next;
	}
	return (true);
}

static bool	check_first_token(t_token *tokens)
{
	if (!tokens)
		return (true);
	if (tokens->type == PIPE)
	{
		printf(RED "Syntax error: unexpected token\n" RESET);
		return (false);
	}
	return (true);
}

bool	valid_syntax(t_token *tokens)
{
	t_token	*current;
	bool	cmd_before;

	if (!check_first_token(tokens))
		return (false);
	cmd_before = false;
	current = tokens;
	while (current)
	{
		if (!process_token(&current, &cmd_before))
			return (false);
		current = current->next;
	}
	if (!cmd_before)
	{
		printf(RED "Syntax error: unexpected token '|'\n" RESET);
		return (false);
	}
	return (true);
}
