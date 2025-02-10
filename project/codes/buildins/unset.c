/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgomes-p <vgomes-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 14:28:07 by vgomes-p          #+#    #+#             */
/*   Updated: 2025/02/10 13:37:02 by vgomes-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	rmvar(char *var, char ***envp)
{
	size_t	index;
	char	*tempvar;

	index = 0;
	if (!var || !envp || !*envp)
		return ;
	tempvar = ft_strjoin (var, "=");
	if (!tempvar)
		return ;
	while ((*envp)[index] && ft_strncmp((*envp)[index],
			tempvar, ft_strlen(tempvar)))
		index++;
	if ((*envp)[index])
	{
		free((*envp)[index]);
		while ((*envp)[index])
		{
			(*envp)[index] = (*envp)[index + 1];
			index++;
		}
		(*envp)[index] = NULL;
	}
	free(tempvar);
}

static void	unset_err(const char *arg)
{
	ft_putstr_fd(ORANGE "unset: " YELLOW "\"", STDERR_FILENO);
	ft_putstr_fd((char *)arg, STDERR_FILENO);
	ft_putstr_fd("\"" ORANGE " not found\n" RESET, STDERR_FILENO);
}

static void	unset_usage(void)
{
	ft_putstr_fd(YELLOW "usage: unser <var name>\n" RESET, STDERR_FILENO);
}

static int	validvar(const char *var, char ***envp)
{
	int		varlen;
	char	*var_eq;
	int		index;

	if (!var || !envp || !*envp)
		return (0);
	varlen = ft_strlen(var);
	var_eq = ft_strjoin(var, "=");
	if (!var_eq)
		return (0);
	index = 0;
	while ((*envp)[index])
	{
		if (ft_strncmp((*envp)[index], var_eq, varlen + 1) == 0)
		{
			free(var_eq);
			return (1);
		}
		index++;
	}
	free(var_eq);
	return (0);
}

void	ms_unset(t_minishell *shell, char **args, char ***envp)
{
	if (!args[1])
	{
		unset_usage();
		shell->error_code = 1;
		return ;
	}
	if (!envp || !*envp)
	{
		shell->error_code = 1;
		return ;
	}
	while (*(++args))
	{
		if (validvar(*args, envp))
		{
			rmvar(*args, envp);
		}
		else
		{
			unset_err(*args);
			shell->error_code = 1;
		}
	}
	shell->error_code = 0;
}
