/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgomes-p <vgomes-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 17:10:12 by vgomes-p          #+#    #+#             */
/*   Updated: 2025/01/27 17:46:04 by vgomes-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_token	*tokening(const char *input)
{
	t_token		head;
	t_token		*current;
	int			index;
	char		quote;
	int			start;
	t_token_tp	type;

	head = NULL;
	current = NULL;
	index = 0;

	while (input[index] != '\0')
	{
		if (input[index] == ' ' || input[index] == '\t')
		{
			index++;
			continue;
		}
		else if (input[index] == '\'' || input[index] == '"')
		{
			quote = input[index++];
			start = index;
			while (input[index] != '\0' && input[index] != quote)
				index++;
			if (input[index] == quote)
			{
				add_token(&head, &current, ft_substr(input, start, index - start), ARG)
				index++;
			}
			else
			{
				handle_error("unclosed quote");
				free_tokens(head);
				return (NULL);
			}
		}
		else if (input[index] == '>' || input[index] == '<' || input[index] == '|')
		{
			type = PIPE;
			if (input[index] == '>')
			{
				type = (input[index + 1] == '>') ? APPEND : REDIR_OUT;
				index += (type == APPEND) ? 2 : 1;
			}
			else if (input[index] == '<')
			{
				type = REDIR_IN;
				index++;
			}
			else
				index ++;
			add_token(&head, &current, ft_substr(input, index - 1, 1), type);
		}
		else
		{
			start = index;
			while (input[index] != '\0' && input[index] != ' ' && input[index] != '\t' &&
				input[index] != '>' && input[index] != '<' && input[index] != '|')
			{
				index++;
			}
			add_token(&head, &current, ft_substr(input, start, index - start), CMD);
		}
	}
	return (head);
}
