/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgomes-p <vgomes-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 16:15:00 by vgomes-p          #+#    #+#             */
/*   Updated: 2025/02/17 15:49:11 by vgomes-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ms_pwd(t_minishell *shell)
{
	char	*cwd;
	int		pwd_index;
	char	*pwd_env;

	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		ft_putstr_fd(RED "pwd: error" RESET, 2);
		return ;
	}
	pwd_env = ft_strjoin("PWD=", cwd);
	if (!pwd_env)
	{
		free(cwd);
		return ;
	}
	ft_putstr_fd(cwd, STDOUT_FILENO);
	ft_putstr_fd("\n", STDOUT_FILENO);
	pwd_index = find_envar("PWD", shell->env);
	update_envar(pwd_env, pwd_index, &shell->env);
	free(pwd_env);
	free(cwd);
}
