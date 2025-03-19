/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgomes-p <vgomes-p@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 01:09:12 by vgomes-p          #+#    #+#             */
/*   Updated: 2025/03/18 01:09:12 by vgomes-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static t_exec	init_exec_data(t_minishell *shell, t_token *tokens)
{
	t_exec	exec;

	(void)shell;
	exec.tokens_head = tokens;
	exec.temp = tokens;
	exec.pid = NULL;
	exec.stts = 0;
	exec.nbr_pros = 1;
	exec.cmd = tokens_matrix(exec.temp);
	if (!exec.cmd)
	{
		exec.fd = NULL;
		return (exec);
	}
	while (exec.temp)
	{
		if (exec.temp->type == PIPE)
			exec.nbr_pros++;
		exec.temp = exec.temp->next;
	}
	return (exec);
}

static t_exec	init_exec_struct(t_minishell *shell, t_token *tokens)
{
	t_exec	exec;

	exec = init_exec_data(shell, tokens);
	if (!exec.cmd)
		return (exec);
	if (exec.nbr_pros <= 0)
	{
		free_matrix(&exec.cmd);
		exec.fd = NULL;
		return (exec);
	}
	if (!allocate_pipes(&exec))
	{
		free_matrix(&exec.cmd);
		exec.fd = NULL;
		return (exec);
	}
	return (exec);
}

t_exec	init_exec(t_minishell *shell, t_token *tokens)
{
	t_exec	exec;
	int		ind;

	exec = init_exec_struct(shell, tokens);
	if (!exec.cmd || exec.nbr_pros <= 0 || !exec.fd)
		return (exec);
	exec.cmd_tokens = ft_calloc(exec.nbr_pros, sizeof(t_token *));
	if (!exec.cmd_tokens)
	{
		free_matrix(&exec.cmd);
		if (exec.fd)
		{
			ind = 0;
			while (ind < exec.nbr_pros - 1)
			{
				free(exec.fd[ind]);
				ind++;
			}
			free(exec.fd);
		}
		exec.fd = NULL;
		return (exec);
	}
	exec.temp = exec.tokens_head;
	return (exec);
}
