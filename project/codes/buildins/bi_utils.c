/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgomes-p <vgomes-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 13:57:13 by vgomes-p          #+#    #+#             */
/*   Updated: 2025/02/13 19:23:33 by vgomes-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	find_envar(const char *var, char **envp)
{
	char	*findkey;
	int		varlen;
	int		index;
	char	*equal_sign;

	equal_sign = ft_strchr(var, '=');
	if (equal_sign)
		varlen = equal_sign - var;
	else
		varlen = ft_strlen(var);
	findkey = ft_calloc(varlen + 2, sizeof(char));
	ft_strlcpy(findkey, var, varlen + 2);
	findkey[varlen] = '=';
	findkey[varlen + 1] = '\0';
	index = 0;
	while (envp[index] && ft_strncmp(envp[index], findkey, varlen + 1))
		index++;
	free(findkey);
	return (index);
}

static int	add_new_envar(const char *var, char ***envp, int envsz)
{
	char	**nwenv;
	int		index1;

	nwenv = ft_calloc(envsz + 2, sizeof(char *));
	if (!nwenv)
		return (0);
	index1 = -1;
	while (++index1 < envsz)
	{
		nwenv[index1] = ft_strdup((*envp)[index1]);
		if (!nwenv[index1])
		{
			while (--index1 >= 0)
				free(nwenv[index1]);
			free(nwenv);
			return (0);
		}
	}
	nwenv[envsz] = ft_strdup(var);
	if (!nwenv[envsz])
	{
		while (--envsz >= 0)
			free(nwenv[envsz]);
		free(nwenv);
		return (0);
	}
	*envp = nwenv;
	return (1);
}

void	update_envar(const char *var, int index0, char ***envp)
{
	int		envsz;
	int		index1;
	char	**old_env;

	envsz = 0;
	while (*envp && (*envp)[envsz])
		envsz++;
	if (index0 < envsz)
	{
		free((*envp)[index0]);
		(*envp)[index0] = ft_strdup(var);
		return ;
	}
	old_env = *envp;
	if (!add_new_envar(var, envp, envsz))
		return ;
	index1 = -1;
	while (++index1 < envsz)
		free(old_env[index1]);
	free(old_env);
}

int	valid_name(const char *var)
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

void	export_err(const char *arg)
{
	ft_putstr_fd(RED "export: " ORANGE "\"", STDERR_FILENO);
	ft_putstr_fd((char *)arg, STDERR_FILENO);
	ft_putstr_fd("\"" RED " not a valid indentifier\n" RESET, STDERR_FILENO);
}
