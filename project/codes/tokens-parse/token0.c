/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token0.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgomes-p <vgomes-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 16:18:44 by vgomes-p          #+#    #+#             */
/*   Updated: 2025/02/10 19:06:48 by vgomes-p         ###   ########.fr       */
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

void	define_special_type(t_token *token)
{
	if (lms_strcmp(token->value, "|") == 0)
		token->type = PIPE;
	else if (lms_strcmp(token->value, ">") == 0)
		token->type = REDIR_OUT;
	else if (lms_strcmp(token->value, ">>") == 0)
		token->type = REDIR_APPEND;
	else if (lms_strcmp(token->value, "<") == 0)
		token->type = REDIR_IN;
	else if (lms_strcmp(token->value, "<<") == 0)
		token->type = HEREDOC;
	else if (is_buildin(token->value))
		token->type = BUILDIN;
}

void	define_type(t_token **head)
{
	t_token	*token;

	token = *head;
	while (token)
	{
		define_special_type(token);
		if (token->type == 0)
		{
			if (!token->prev || token->prev->type == PIPE)
				token->type = CMD;
			else if (token->prev->prev->type >= REDIR_OUT
				&& token->prev->type <= HEREDOC)
				token->type = ARG_FILE;
			else
				token->type = ARG;
		}
		token = token->next;
	}
}

void	add_token(t_token **head, char *value)
{
	t_token	*new;
	t_token	*temp;

	new = ft_calloc(1, sizeof(t_token));
	new->value = ft_strdup(value);
	new->next = NULL;
	if (!head)
	{
		*head = new;
		new->prev = NULL;
		return ;
	}
	temp = *head;
	while (temp->next)
		temp = temp->next;
	new->prev = temp;
	temp->next = new;
}

t_token	*tokening(char *input)
{
	char	**split;
	t_token	*head;
	int		pos;

	split = ms_split_quotes(input);
	if (!split)
		return (NULL);
	pos = 0;
	while (split[pos])
	{
		add_token(&head, split[pos]);
		pos++;
	}
	free_split_array(split);
	return (head);
}
