/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgomes-p <vgomes-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 15:53:14 by vgomes-p          #+#    #+#             */
/*   Updated: 2025/02/06 15:54:02 by vgomes-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	rmvar(char *var, char ***envp)
{
	size_t	index;
	char	*tempvar;

	index = 0;
	if (!var || !envp)
		return ;
	tempvar = ft_strjoin (var, "=");
	while (envp[0][index] && ft_strncmp(envp[0][index], tempvar, ft_strlen(tempvar)))
		index++;
	if (*envp && envp[0][index])
	{
		free(envp[0][index]);
		envp[0][index] = envp[0][index + 1];
		index++;
		while (envp[0][index])
		{
			envp[0][index] = envp[0][index + 1];
			index++;
		}
		envp[0][index] = NULL;
	}
	free(tempvar);
}

void	ms_unset(t_minishell *shell, char **args, char ***envp)
{
	while (*(++args))
		rmvar(*args, envp);
	shell->error_code = 0;
}
