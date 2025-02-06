/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgomes-p <vgomes-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 15:53:11 by vgomes-p          #+#    #+#             */
/*   Updated: 2025/02/06 15:53:50 by vgomes-p         ###   ########.fr       */
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

void	update_envar(const char *var, int index0, char ***envp)
{
	char	**nwenv;
	int		envsz;
	int		index1;

	envsz = 0;
	while (*envp && (*envp)[envsz])
		envsz++;
	if (index0 < envsz)
	{
		free((*envp)[index0]);
		(*envp)[index0] = ft_strdup(var);
	}
	else
	{
		nwenv = ft_calloc(envsz + 2, sizeof(char *));
		index1 = -1;
		while (++index1 < envsz)
			nwenv[index1] = ft_strdup((*envp)[index1]);
		nwenv[envsz] = ft_strdup(var);
		free(*envp);
		*envp = nwenv;
	}
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
