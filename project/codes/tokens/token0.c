/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token0.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgomes-p <vgomes-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 16:18:44 by vgomes-p          #+#    #+#             */
/*   Updated: 2025/02/04 16:47:37 by vgomes-p         ###   ########.fr       */
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

static void	free_split_array(char **split)
{
	int	index1;

	index1 = 0;
	while (split[index1])
	{
		free(split[index1]);
		index1++;
	}
	free(split);
}

static t_token	*create_token_list(char **split, t_token *head)
{
	t_token	*current;
	t_token	*nwtoken;
	int		index0;

	current = NULL;
	index0 = 0;
	while (split[index0])
	{
		nwtoken = mktoken(split[index0],
				get_token_type(split[index0], current, index0 == 0));
		if (!nwtoken)
		{
			free_split_array(split);
			free_tokens(head);
			return (NULL);
		}
		if (!head)
			head = nwtoken;
		else
			current->next = nwtoken;
		current = nwtoken;
		index0++;
	}
	return (head);
}

t_token	*tokening(char *input)
{
	char	**split;
	t_token	*head;

	split = ms_split_quotes(input);
	if (!split)
		return (NULL);
	head = NULL;
	head = create_token_list(split, head);
	if (head)
		free_split_array(split);
	return (head);
}
