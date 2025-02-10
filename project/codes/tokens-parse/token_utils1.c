/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgomes-p <vgomes-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 16:51:45 by vgomes-p          #+#    #+#             */
/*   Updated: 2025/02/10 19:11:36 by vgomes-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

bool	valid_syntax(t_token *tokens)
{
	t_token	*current;

	current = tokens;
	while (current)
	{
		if (current->type == PIPE && (!current->prev || !current->next))
		{
			ft_putstr_fd(RED "Syntax error near unexpected pipe\n" RESET, 2);
			return (false);
		}
		else if ((current->type >= REDIR_IN && current->type <= HEREDOC) && !current->next)
		{
			ft_putstr_fd(RED "syntax error near unexpected 'newline'\n" RESET, 2);
			return (false);
		}
		current = current->next;
	}
	return (true);
}

void	cleanup_tokens(char **tokens, int token_cnt)
{
	int	pos;

	pos = 0;
	while (pos < token_cnt)
	{
		free(tokens[pos]);
		pos++;
	}
	free(tokens);
}

void	free_split_array(char **split)
{
	int	pos;

	pos = 0;
	while (split[pos])
	{
		free(split[pos]);
		pos++;
	}
	free(split);
}
