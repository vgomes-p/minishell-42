/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_buildins.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgomes-p <vgomes-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 18:11:40 by vgomes-p          #+#    #+#             */
/*   Updated: 2025/01/14 18:48:01 by vgomes-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ms_exec_builtin(char **tokens, t_minishell *shell)
{
	if (ft_strcmp(tokens[0], "cd") == 0)
		ms_cd(tokens);
	else if (ft_strcmp(tokens[0], "echo") == 0)
		ms_echo(tokens);
	else if (ft_strcmp(tokens[0], "exit") == 0)
		ms_exit(tokens, shell);
	else if (ft_strcmp(tokens[0], "env") == 0)
		ms_env();
	else if (ft_strcmp(tokens[0], "export") == 0)
		ms_export(tokens);
	else if (ft_strcmp(tokens[0], "unset") == 0)
		ms_unset(tokens);
	else if (ft_strcmp(tokens[0], "pwd") == 0)
		ms_pwd();
	else
		ft_putstr_fd("command not found\n", 2);
}

void	ms_process_buildin(char *input, t_minishell *shell)
{
	char	**tokens;
	int		index;

	tokens = ft_split(input, ' ');
	if (!tokens || !tokens[0])
	{
		free(tokens);
		return ;
	}
	ms_exec_builtin(tokens, shell);
	index = 0;
	while (tokens[index])
	{
		free(tokens[index]);
		index++;
	}
	free(tokens);
}
