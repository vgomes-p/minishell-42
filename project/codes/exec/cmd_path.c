/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgomes-p <vgomes-p@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 18:33:07 by vgomes-p          #+#    #+#             */
/*   Updated: 2025/03/08 03:50:46 by vgomes-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_full_path(char *cmd, char **path_dir)
{
	int		pos;
	char	*full_path;
	char	*temp;

	pos = -1;
	full_path = NULL;
	while (path_dir && path_dir[++pos])
	{
		temp = ft_strjoin(path_dir[pos], "/");
		full_path = ft_strjoin(temp, cmd);
		temp = free_ptr(temp);
		if ((!access(full_path, F_OK)) && !access(full_path, X_OK))
			break ;
		full_path = free_ptr(full_path);
	}
	return (full_path);
}

char	*find_exec_path(char *cmd, char **envp)
{
	int		pos;
	char	**path_dir;
	char	*full_path;

	if (cmd[0] == '/' || cmd[0] == '.')
	{
		if ((!access(cmd, F_OK)) && !access(cmd, X_OK) && ft_strlen(cmd) > 2)
			return (cmd);
		return (NULL);
	}
	pos = -1;
	while (envp && envp[++pos])
	{
		if (!ft_strncmp("PATH=", envp[pos], 5))
			break ;
	}
	if (envp[pos] == NULL)
		return (NULL);
	path_dir = ft_split(envp[pos] + 5, ':');
	full_path = get_full_path(cmd, path_dir);
	free_matrix(&path_dir);
	path_dir = NULL;
	return (full_path);
}
