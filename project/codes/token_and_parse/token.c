/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgomes-p <vgomes-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 16:18:44 by vgomes-p          #+#    #+#             */
/*   Updated: 2025/02/13 19:12:42 by vgomes-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_token	*mktoken(char *value, t_token_tp type)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->value = ft_strdup(value);
	if (!token->value)
		free(token);
	token->type = type;
	token->next = NULL;
	return (token);
}

char	**ms_split_quotes(const char *input)
{
	char	**tokens;

	tokens = ft_calloc(ft_strlen(input) + 1, sizeof(char *));
	if (!tokens)
		return (NULL);
	return (process_tokens(input, tokens));
}

t_token	*create_token_list(char **split, t_token *head)
{
	t_token	*current;
	t_token	*nwtoken;
	int		pos;

	pos = 0;
	while (split[pos])
	{
		nwtoken = mktoken(split[pos],
				get_token_type(split[pos], current, pos == 0));
		if (!nwtoken)
		{
			free_split(split);
			free_tokens(head);
			return (NULL);
		}
		if (!head)
			head = nwtoken;
		else
			current->next = nwtoken;
		current = nwtoken;
		pos++;
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
	head = create_token_list(split, NULL);
	if (!head)
	{
		free_split(split);
		return (NULL);
	}
	free_split(split);
	return (head);
}
