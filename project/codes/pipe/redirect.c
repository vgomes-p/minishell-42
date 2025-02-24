/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sthrodri <sthrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 15:59:14 by vgomes-p          #+#    #+#             */
/*   Updated: 2025/02/24 13:54:20 by sthrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	is_redin(t_minishell *ms, char **cmd, int pos)
{
	static int	file;

	file = -1;
	if (!ft_strncmp(cmd[pos], "<", 2))
	{
		file = open(cmd[pos + 1], O_RDONLY);
		if (file == -1)
			return (-5);
	}
	else if (!ft_strncmp(cmd[pos], "<<", 3))
		file = heredoc(ms, cmd[pos + 1], ms->env);
	return (file);
}

static int	is_redout(char **cmd, int pos)
{
	static int	file;

	file = -1;
	if (!ft_strncmp(cmd[pos], ">", 2))
	{
		file = open(cmd[pos + 1], O_WRONLY | O_CREAT | O_TRUNC, 0777);
		if (file == -1)
			return (-5);
	}
	else if (!ft_strncmp(cmd[pos], ">>", 3))
	{
		file = open(cmd[pos + 1], O_APPEND | O_WRONLY | O_CREAT, 0777);
		if (file == -1)
			return (-5);
	}
	return (file);
}

static int	is_redirect(char *cmd)
{
	return (!ft_strncmp(cmd, ">", 2) || !ft_strncmp(cmd, ">>", 3) 
		|| !ft_strncmp(cmd, "<", 2) || !ft_strncmp(cmd, "<<", 3));
}

void	set_redirect(t_minishell *ms, char **cmd, int *fd, char **ret)
{
	int	pos;
	int	cnt;

	pos = 0;
	cnt = 0;
	while (cmd[pos])
	{
		if (is_redirect(cmd[pos]))
		{
			fd[0] = is_redin(ms, cmd, pos);
			fd[1] = is_redout(cmd, pos);
			pos += 2;
			if (fd[0] == -5 || fd[1] == -5)
				break ;
		}
		else
			ret[cnt++] = ft_strdup(cmd[pos++]);
	}
	sfree(cmd);
}

static void	init_fd(int *fd)
{
	fd[0] = -1;
	fd[1] = -1;
}

char	**redirect(t_minishell *ms, char **cmd, int *out, int *in)
{
	int	fd[2];
	int	cnt;
	char	**ret;

	init_fd(fd);
	cnt = 0;
	while (cmd[cnt])
		cnt++;
	ret = ft_calloc(cnt + 1, sizeof(char *));
	set_redirect(ms, cmd, fd, ret);
	if (fd[0] == -5 || fd[1] == -5)
	{
		sfree(ret);
		return (NULL);
	}
	if (fd[0] != -1)
	{
		dup2(fd[0], 0);
		close(fd[0]);
		*in = 1;
	}
	if (fd[1] != -1)
	{
		dup2(fd[1], 1);
		close(fd[1]);
		*out = 1;
	}
	return (ret);
}
