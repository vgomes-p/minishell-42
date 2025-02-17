/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_externs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgomes-p <vgomes-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 17:39:11 by vgomes-p          #+#    #+#             */
/*   Updated: 2025/02/17 16:33:21 by vgomes-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	exec_extern(t_token *tokens, t_minishell *shell)
{
	char	**args;
	pid_t	pid;

	args = prepare_args(tokens);
	if (!args)
		return ;
	pid = fork();
	if (pid == 0)
	{
		if (access(args[0], X_OK) == -1)
		{
			ft_putstr_fd(RED "command not found\n" RESET, 2);
			free_split(args);
			exit(127);
		}
		if (execve(args[0], args, shell->env) == -1)
		{
			perror(RED "execve" RESET);
			free_split(args);
			exit(EXIT_FAILURE);
		}
	}
	else if (pid < 0)
		perror(RED "fork" RESET);
	else
		waitpid(pid, NULL, 0);
	free_split(args);
}
