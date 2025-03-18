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

t_exec	init_exec(t_minishell *shell, t_token *tokens)
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
	exec.temp = exec.tokens_head;
	return (exec);
}
