/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgomes-p <vgomes-p@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 18:28:41 by vgomes-p          #+#    #+#             */
/*   Updated: 2025/03/08 03:50:17 by vgomes-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	exec_extern(char **cmd, char **envp)
{
	char	*path;
	char	*error;
	char	*temp;

	path = find_exec_path(cmd[0], envp);
	if (!path)
	{
		ft_putstr_fd(RED "Command " ORANGE, 2);
		ft_putstr_fd(cmd[0], 2);
		ft_putstr_fd(RED " was not found\n" RESET, 2);
		free_matrix(&cmd);;
		exit(127);
	}
	execve(path, cmd, envp);
	path = free_ptr(path);
	error = ft_strjoin(RED, cmd[0]);
	temp = error;
	error = lms_strjoin_free(error, " : execution failed!\n" RESET);
	free(temp);
	perror(error);
	error = free_ptr(error);
	exit(EXIT_FAILURE);
}

void	clean_child_res(t_minishell *shell, char **cmd, int **fd, int code)
{
	int	pos;

	shell->error_code = code;
	free_matrix(&cmd);
	cmd = NULL;
	pos = 0;
	if (fd)
	{
		while (fd[++pos])
		{
			fd[pos] = (int *) free_ptr((char *) fd[pos]);
			pos++;
		}
		sfree_int(fd);
		fd = NULL;
	}
	rl_clear_history();
	unlink("__heredoc");
	exit(shell->error_code);
}

void	file_errmsg(t_minishell *shell, char *cmd)
{
	char	*color_cmd;

	color_cmd = ft_strjoin(RED, cmd);
	ft_putstr_fd(color_cmd, 2);
	free(color_cmd);
	shell->error_code = 1;
}

void	handle_invalid_file(t_minishell *shell)
{
	t_token	*temp;

	temp = shell->tokens;
	while (temp)
	{
		if (temp->type == HEREDOC)
			shell->error_code = 0;
		if (temp->type == ARG)
		{
			if (access(temp->value, F_OK))
			{
				file_errmsg(shell, temp->value);
				ft_putstr_fd(": No such file or directory\n" RESET, 2);
			}
			else if (access(temp->value, R_OK) || access(temp->value, W_OK))
			{
				file_errmsg(shell, temp->value);
				ft_putstr_fd(": Permission Denied\n", 2);
				shell->error_code = 1;
			}
		}
		temp = temp->next;
	}
}

void	child(t_minishell *shell, char **cmd, int **fd, int pos)
{
	int	in;
	int	out;

	in = 0;
	out = 0;
	if (!cmd || *cmd == NULL)
	{
		handle_invalid_file(shell);
		clean_child_res(shell, NULL, fd, shell->error_code);
	}
	if (pos && !in)
		dup2(fd[pos -1][0], 0);
	if (fd[pos] && !out)
		dup2(fd[pos][1], 1);
	cls_fd(fd);
	exec_extern(cmd, shell->env);
	clean_child_res(shell, cmd, fd, shell->error_code);
}
