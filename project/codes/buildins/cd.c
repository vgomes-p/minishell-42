/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgomes-p <vgomes-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 16:13:12 by vgomes-p          #+#    #+#             */
/*   Updated: 2025/02/13 16:40:50 by vgomes-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	update_pwd(char *oldpwd, t_minishell *shell)
{
	char	*nwpwd;
	int		index_oldpwd;
	int		pwd_index;
	char	*oldpwd_var;
	char	*pwd_var;

	nwpwd = getcwd(NULL, 0);
	if (!nwpwd)
	{
		perror(RED "cd: getcwd" RESET);
		free(oldpwd);
		return ;
	}
	index_oldpwd = find_envar("OLDPWD", shell->env);
	oldpwd_var = ft_strjoin("OLDPWD=", oldpwd);
	update_envar(oldpwd_var, index_oldpwd, &shell->env);
	pwd_index = find_envar("PWD", shell->env);
	pwd_var = ft_strjoin("PWD=", nwpwd);
	update_envar(pwd_var, pwd_index, &shell->env);
	free(oldpwd);
	free(nwpwd);
	free(oldpwd_var);
	free(pwd_var);
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
