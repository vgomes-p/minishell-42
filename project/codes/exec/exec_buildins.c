/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_buildins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgomes-p <vgomes-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 16:17:33 by vgomes-p          #+#    #+#             */
/*   Updated: 2025/03/06 15:59:21 by vgomes-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	check_builtin_type(char **args, t_minishell *shell, int *ret)
{
	*ret = 1;
	if (lms_strcmp(args[0], "cd") == 0)
		ms_cd(args, shell);
	else if (lms_strcmp(args[0], "echo") == 0)
		ms_echo(args);
	else if (lms_strcmp(args[0], "env") == 0)
		ms_env(shell);
	else if (lms_strcmp(args[0], "exit") == 0)
		ms_exit(args, shell);
	else if (lms_strcmp(args[0], "pwd") == 0)
		ms_pwd(shell);
	else if (lms_strcmp(args[0], "export") == 0)
	{
		ms_export(shell, args, &shell->env);
		if (shell->error_code != 0)
			*ret = shell->error_code;
	}
	else if (lms_strcmp(args[0], "unset") == 0)
		ms_unset(shell, args, &shell->env);
	else
		*ret = 0;
	return (*ret);
}

int	exec_builtin(t_token *tokens, t_minishell *shell)
{
	char	**args;
	int		ret;

	args = prepare_args(tokens);
	if (!args)
		return (-1);
	ret = check_builtin_type(args, shell, &ret);
	sfree(args);
	return (ret);
}
