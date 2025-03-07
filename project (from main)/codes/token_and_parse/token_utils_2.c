/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgomes-p <vgomes-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 18:25:59 by vgomes-p          #+#    #+#             */
/*   Updated: 2025/02/21 14:25:48 by vgomes-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**tokens_matrix(t_token *token)
{
	int		cnt;
	int		pos;
	char	**ret;

	if (!token)
		return (NULL);
	cnt = count_tokens(token);
	ret = ft_calloc((cnt + 1), sizeof(char *));
	if (!ret)
		return (NULL);
	pos = 0;
	while (pos < cnt)
	{
		ret[pos] = ft_strdup(token->value);
		if (!ret[pos])
		{
			sfree(ret);
			return (NULL);
		}
		token = token->next;
		pos++;
	}
	ret[pos] = NULL;
	return (ret);
}

t_token	*cpy_token_ls(t_token *tokens)
{
	t_token	*new_list;
	t_token	*current;
	t_token	*new_token;

	if (!tokens)
		return (NULL);
	new_list = NULL;
	current = tokens;
	while (current)
	{
		new_token = mktoken(current->value, current->type);
		if (!new_token)
		{
			free_tokens(new_list);
			return (NULL);
		}
		if (!new_list)
			new_list = new_token;
		else
			addtoken_ls(new_list, new_token);
		current = current->next;
	}
	return (new_list);
}

void	addtoken_ls(t_token *list, t_token *new_token)
{
	t_token	*current;

	if (!list || !new_token)
		return ;
	current = list;
	while (current->next)
		current = current->next;
	current->next = new_token;
}
