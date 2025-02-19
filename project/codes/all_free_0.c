/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   all_free_0.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgomes-p <vgomes-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 13:45:43 by vgomes-p          #+#    #+#             */
/*   Updated: 2025/02/19 19:32:53 by vgomes-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_env(char **env)
{
	int	pos;

	if(!env)
		return ;
	pos = 0;
	while (env[pos])
	{
		free(env[pos]);
		pos++;
	}
	free(env);
}
void	free_tokens(t_token *tokens)
{
	t_token	*current;
	t_token	*next;

	current = tokens;
	while (current)
	{
		next = current->next;
		free(current->value);
		free(current);
		current = next;
	}
}

void	sfree(char **split)
{
	int	pos;

	if (!split)
		return ;
	pos = 0;
	while (split[pos])
	{
		free(split[pos]);
		pos++;
	}
	free(split);
}

char	*free_ptr(char *ptr)
{
	free(ptr);
	ptr = NULL;
	return (NULL);
}

void	sfree_int(int **fd)
{
	int	pos;

	if (!fd)
		return;
	pos = 0;
	while (fd[pos])
	{
		free(fd[pos]);
		pos++;
	}
	free(fd);
}
