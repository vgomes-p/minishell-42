/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgomes-p <vgomes-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 16:13:12 by vgomes-p          #+#    #+#             */
/*   Updated: 2025/02/12 17:56:07 by vgomes-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	update_pwd(char *oldpwd, t_minishell *shell)
{
	char	*nwpwd;
	int		index_oldpwd;
	int		pwd_index;

	nwpwd = getcwd(NULL, 0);
	if (!nwpwd)
	{
		perror(RED "cd: getcwd" RESET);
		free(oldpwd);
		return ;
	}
	index_oldpwd = find_envar("OLDPWD", shell->env);
	update_envar(ft_strjoin("OLDPWD=", oldpwd), index_oldpwd, &shell->env);
	pwd_index = find_envar("PWD", shell->env);
	update_envar(ft_strjoin("PWD=", nwpwd), pwd_index, &shell->env);
	free(oldpwd);
	free(nwpwd);
}

static void	handle_home_cd(char *oldpwd, t_minishell *shell)
{
	char	*home;

	home = getenv("HOME");
	if (!home)
	{
		ft_putstr_fd(RED "cd: HOME not set" RESET, 2);
		free(oldpwd);
		return ;
	}
	if (chdir(home) == -1)
	{
		free(oldpwd);
		perror(RED "cd" RESET);
		return ;
	}
	update_pwd(oldpwd, shell);
}

void	ms_cd(char **args, t_minishell *shell)
{
	char	*oldpwd;

	oldpwd = getcwd(NULL, 0);
	if (!oldpwd)
	{
		perror("cd");
		return ;
	}
	if (!args[1])
		handle_home_cd(oldpwd, shell);
	else if (chdir(args[1]) == -1)
	{
		free(oldpwd);
		perror(RED "cd" RESET);
		return ;
	}
	else
		update_pwd(oldpwd, shell);
}
