/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgomes-p <vgomes-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 16:13:12 by vgomes-p          #+#    #+#             */
/*   Updated: 2025/02/21 11:55:13 by vgomes-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*get_new_pwd(char *oldpwd)
{
	char	*nwpwd;

	nwpwd = getcwd(NULL, 0);
	if (!nwpwd)
	{
		perror(RED "cd: getcwd" RESET);
		free(oldpwd);
		return (NULL);
	}
	return (nwpwd);
}

static int	update_oldpwd(char *oldpwd, t_minishell *shell)
{
	int		index_oldpwd;
	char	*oldpwd_var;

	index_oldpwd = find_envar("OLDPWD", shell->env);
	oldpwd_var = ft_strjoin("OLDPWD=", oldpwd);
	if (!oldpwd_var)
		return (0);
	update_envar(oldpwd_var, index_oldpwd, &shell->env);
	free(oldpwd_var);
	return (1);
}

static void	update_pwd(char *oldpwd, t_minishell *shell)
{
	char	*nwpwd;
	int		pwd_index;
	char	*pwd_var;

	nwpwd = get_new_pwd(oldpwd);
	if (!nwpwd)
		return ;
	if (!update_oldpwd(oldpwd, shell))
	{
		free(nwpwd);
		free(oldpwd);
		return ;
	}
	pwd_index = find_envar("PWD", shell->env);
	pwd_var = ft_strjoin("PWD=", nwpwd);
	if (!pwd_var)
	{
		free(nwpwd);
		free(oldpwd);
		return ;
	}
	update_envar(pwd_var, pwd_index, &shell->env);
	free(pwd_var);
	free(nwpwd);
	free(oldpwd);
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
		perror(RED "cd" RESET);
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
