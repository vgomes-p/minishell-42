/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils_0.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgomes-p <vgomes-p@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 17:41:12 by vgomes-p          #+#    #+#             */
/*   Updated: 2025/03/14 17:08:07 by vgomes-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	count_args(t_token *tokens)
{
	t_token	*current;
	int		arg_count;

	arg_count = 0;
	if (!tokens)
		return (0);
	current = tokens;
	while (current)
	{
		if (current->type == CMD || current->type == ARG)
			arg_count++;
		if (is_redir(current))
			current = current->next;
		if (current)
			current = current->next;
	}
	return (arg_count);
}

static char	**allocate_args_array(int arg_count)
{
	char	**args;

	if (arg_count <= 0)
		return (NULL);
	args = malloc(sizeof(char *) * (arg_count + 1));
	return (args);
}

static int	fill_args_array(char **args, t_token *tokens, int arg_count)
{
	t_token	*current;
	int		arg_pos;

	arg_pos = 0;
	current = tokens;
	while (current && arg_pos < arg_count)
	{
		if (current->type == CMD || current->type == ARG)
		{
			args[arg_pos] = ft_strdup(current->value);
			if (!args[arg_pos])
				return (0);
			arg_pos++;
		}
		if (is_redir(current))
			current = current->next;
		if (current)
			current = current->next;
	}
	args[arg_pos] = NULL;
	return (1);
}

char	**prepare_args(t_token *tokens)
{
	char	**args;
	int		arg_count;

	if (!tokens)
		return (NULL);
	arg_count = count_args(tokens);
	args = allocate_args_array(arg_count);
	if (!args)
		return (NULL);
	if (!fill_args_array(args, tokens, arg_count))
	{
		free_matrix(&args);
		return (NULL);
	}
	return (args);
}

void	cls_fd(int **fd)
{
	int	pos;

	pos = 0;
	while (fd[pos])
	{
		close(fd[pos][0]);
		close(fd[pos][1]);
		pos++;
	}
}
