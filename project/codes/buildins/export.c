/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sthrodri <sthrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 15:59:22 by vgomes-p          #+#    #+#             */
/*   Updated: 2025/02/17 16:41:20 by sthrodri         ###   ########.fr       */
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
			if (index1 == -1)
			{
				char **new_env = ft_calloc((index0 + 2), sizeof(char *));
				if (!new_env)
				{
					ft_putstr_fd("Error: memory allocation failure for environment variable \n", 2);
					return ;
				}
				new_env[index0] = ft_strdup(args[index0]);
				if (!new_env[index0])
				{
					ft_putstr_fd("Error: failed to duplicate environment variable\n", 2);
					free(new_env);
					return ;
				}
				*envp = new_env;
			}
			else
			{
				update_envar(args[index0], index1, envp);
			}
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
