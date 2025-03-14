/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgomes-p <vgomes-p@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 15:05:21 by vgomes-p          #+#    #+#             */
/*   Updated: 2025/03/14 17:58:40 by vgomes-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	parser(t_token **head, char *str)
{
	*head = tokening(str);
	if (!*head)
	{
		ft_putstr_fd(RED "error: unclosed quotes\n" RESET, 2);
		return (1);
	}
	if (!valid_syntax(*head))
	{
		free_tokens(*head);
		*head = NULL;
		return (1);
	}
	return (0);
}
// bool	valid_syntax(t_token *tokens)
// {
// 	t_token	*current;
// 	bool	cmd_before;

// 	if (!tokens)
// 		return (true);
// 	if (tokens->type == PIPE)
// 	{
// 		printf(RED "Syntax error: unexpected token '|'\n" RESET);
// 		return (false);
// 	}
// 	cmd_before = false;
// 	current = tokens;
// 	while (current)
// 	{
// 		if (current->type == CMD || current->type == ARG)
// 		{
// 			cmd_before = true;
// 		}
// 		else if (current->type == PIPE)
// 		{
// 			if (!cmd_before)
// 			{
// 				printf(RED "Syntax error: unexpected token '|'\n" RESET);
// 				return (false);
// 			}
// 			if (!current->next || (current->next->type != CMD
// 					&& current->next->type != ARG))
// 			{
// 				printf(RED "Syntax error: unexpected token '|'\n" RESET);
// 				return (false);
// 			}
// 			cmd_before = false;
// 		}
// 		else if (current->type == REDIR_OUT || current->type == REDIR_IN
// 			|| current->type == REDIR_APPEND || current->type == HEREDOC)
// 		{
// 			if (!current->next || current->next->type != ARG)
// 			{
// 				printf(RED "Syntax error: '%s' operator without args.\n" RESET,
// 					current->value);
// 				return (false);
// 			}
// 			current = current->next;
// 		}
// 		current = current->next;
// 	}
// 	if (!cmd_before)
// 	{
// 		printf(RED "Syntax error: unexpected token '|'\n" RESET);
// 		return (false);
// 	}
// 	return (true);
// }
