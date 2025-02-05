/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgomes-p <vgomes-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 15:59:22 by vgomes-p          #+#    #+#             */
/*   Updated: 2025/02/05 17:30:11 by vgomes-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	find_envar(const char *var, char **envp)
{
	char	*findkey;
	int		varlen;
	int		index;

	varlen = ft_strchr(var, '=') - var;
	index = 0;
	findkey = ft_calloc(varlen + 2, sizeof(char));
	ft_strlcpy(findkey, var, varlen + 2);
	findkey[varlen] = '=';
	findkey[varlen + 1] = '\0';
	while (envp[index] && ft_strncmp(envp[index], findkey, varlen + 1))
		index++;
	free(findkey);
	return (index);
}

static void update_envar(const char *var, int index0, char ***envp)
{
	char	**nwenv;
	int		index1;

	if (!(*envp)[index0])
	{
		nwenv = ft_calloc(index0 + 2, sizeof(char *));
		nwenv[index0] = ft_strdup(var);
		index1 = index0;
		while (index1--)
			nwenv[index1] = ft_strdup((*envp)[index1]);
		free(*envp);
		*envp = nwenv;
	}
	else
	{
		free((*envp)[index0]);
		(*envp)[index0] = ft_strdup(var);
	}
}

static int	valid_name(const char *var)
{
	int	index;

	index = 0;
	if (!var || var[0] == '=' || ft_isdigit(var[0]))
		return (0);
	while (var[index] && var[index] != '=')
	{
		if (var[index] != '_' && !ft_isalnum(var[index]))
			return (0);
		index++;
	}
	return (1);
}

static void	export_err(const char *arg)
{
	ft_putstr_fd(RED "export: " ORANGE "\"", 2);
	ft_putstr_fd((char *)arg, 2);
	ft_putstr_fd("\"" RED " not a valid indentifier\n" RESET, 2);
}

void	ms_export(t_minishell *shell, char **args, char ***envp)
{
	int	index0;
	int	index1;

	index0 = 1;
	if (!args[1])
	{
		ms_env();
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
	ms_env();
}
