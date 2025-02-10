/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgomes-p <vgomes-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 15:59:22 by vgomes-p          #+#    #+#             */
/*   Updated: 2025/02/06 17:01:51 by vgomes-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ms_export(t_minishell *shell, char **args, char ***envp)
{
	int	index0;
	int	index1;

	index0 = 1;
	if (!args[1])
	{
		ms_env(shell);
		return ;
	}
	while (args[index0])
	{
		if (valid_name(args[index0]))
		{
			index1 = find_envar(args[index0], *envp);
			update_envar(args[index0], index1, envp);
			shell->error_code = 0;
		}
		else
		{
			export_err(args[index0]);
			shell->error_code = 42;
		}
		index0++;
	}
}
