#include "../../includes/minishell.h"

char *get_full_path(char *cmd, char **path_dir)
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
	sfree(path_dir);
	path_dir = NULL;
	return (full_path);
}
/*---------------------------------------------------------------*/
void	cls_fd(int **fd)
{
	int	pos;

	pos = 0;
	while (fd[pos])
	{
		close(fd[pos][0]);
		close(fd[pos][1]);
		pos++;
	}
}
/*---------------------------------------------------------------*/
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
		ft_putstr_fd(RED " was not found\n", 2);
		sfree(cmd);
		cmd = NULL;
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
	sfree(cmd);
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
	ls_clear_history();
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
	cmd = prepare_args(shell->tokens);
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

/*---------------------------------------------------------------*/

char	**tokens_matrix(t_token *token)
{
	int		cnt;
	int		pos;
	char	**ret;

	if (!token)
		return (NULL);
	cnt = count_tokens(token);
	ret = ft_calloc((cnt + 1), sizeof(char *));
	if (!ret)
		return (NULL);
	pos = 0;
	while (pos < cnt)
	{
		ret[pos] = ft_strdup(token->value);
		if (!ret[pos])
		{
			sfree(ret);
			return (NULL);
		}
		token = token->next;
		pos++;
	}
	ret[pos] = NULL;
	return (ret);
}

/*---------------------------------------------------------------*/

t_exec	init_exec(t_minishell *shell)
{
	int		pos;
	t_exec	exec;

	exec.pid = 0;
	exec.stts = 0;
	exec.nbr_pros = 1;
	exec.temp = shell->tokens;
	exec.cmd = tokens_matrix(exec.temp);

	while (exec.temp)
	{
		if (exec.temp->type = PIPE)
			exec.nbr_pros++;
		exec.temp = exec.temp->next;
	}
	exec.fd = ft_calloc(exec.nbr_pros, sizeof(int *));
	pos = -1;
	while (++pos < (exec.nbr_pros - 1))
		exec.fd[pos] = ft_calloc(2, sizeof(int));
	pos = -1;
	while (++pos < exec.nbr_pros - 1)
		pipe(exec.fd[pos]);
	exec.temp = shell->tokens;
	return (exec);
}

int	is_dir(t_minishell *shell, char *cmd)
{
	struct stat	file_info;

	(void)shell;
	if (stat(cmd, &file_info) != 0)
		return (-1);
	if (S_ISDIR(file_info.st_mode))
	{
		ft_putstr_fd(RED, 2);
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": is a directory\n" RESET, 2);
		shell->error_code = 126;
		return (1);
	}
	return (0);
}

int exec_parent(t_minishell *shell, int nb_pros, char **cmd, int **fd)
{
	if (!ft_strncmp(cmd[0], "./", 2) && is_dir(shell, cmd[0]) == 1)
		return (0);
	if (nb_pros > 1)
		return (-1);
	if (exec_builtin(shell->tokens, shell))
	{
		sfree_int(fd);
		fd = NULL;
		return (0);
	}
	return (-1);
}

void	exec_child(t_minishell *shell, t_exec *exec, int pos)
{
	exec->pid = malloc(sizeof(pid_t) * exec->nbr_pros);
	if (!exec->pid)
		return ;
	while (++pos < exec->nbr_pros)
	{
		if (pos)
			exec->cmd = tokens_matrix(exec->temp);
		exec->pid[pos] = fork();
		if (exec->pid[pos] == 0)
			child(shell, exec->cmd, exec->fd, pos);
		while (exec->temp && exec->temp->type != PIPE)
			exec->temp = exec->temp->next;
		if (exec->temp && exec->temp->type == PIPE)
			exec->temp = exec->temp->next;
		sfree(exec->cmd);
		exec->cmd = NULL;
	}
}

// Handle process cleanup and wait for child processes
static void	cleanup_processes(t_exec *exec, t_minishell *shell, int cmd_pos)
{
	int	pros_pos;

	cls_fd(exec->fd);
	pros_pos = -1;
	while (exec->fd[++pros_pos])
		exec->fd[pros_pos] = (int *) free_ptr((char *) exec->fd[pros_pos]);
	sfree_int(exec->fd);
	exec->fd = NULL;
	pros_pos = -1;
	while (++pros_pos < exec->nbr_pros)
		waitpid(exec->pid[pros_pos], &exec->stts, 0);
	if (WIFEXITED(exec->stts) && cmd_pos != exec->nbr_pros)
		shell->error_code = WEXITSTATUS(exec->stts);
	free(exec->pid);
}

// Main execution function for pipe commands
void	exec_pipe_cmd(t_minishell *shell)
{
	int		cmd_pos;
	t_exec	exec;

	if (!shell->tokens || !shell->tokens->value || !*shell->tokens->value)
		return;
	exec = init_exec(shell);
	cmd_pos = exec_parent(shell, exec.nbr_pros, exec.cmd, exec.fd);
	if (cmd_pos > 0)
	{
		sfree(exec.cmd);
		exec.cmd = NULL;
	}
	if (cmd_pos == 0)
		return;
	exec_child(shell, &exec, cmd_pos);
	cleanup_processes(&exec, shell, cmd_pos);
}
/*---------------------------------------------------------------*/
/*---------------------------------------------------------------*/
/*---------------------------------------------------------------*/
/*---------------------------------------------------------------*/
/*---------------------------------------------------------------*/
/*---------------------------------------------------------------*/
/*---------------------------------------------------------------*/
/*---------------------------------------------------------------*/
/*---------------------------------------------------------------*/
/*---------------------------------------------------------------*/
/*---------------------------------------------------------------*/
/*---------------------------------------------------------------*/
/*---------------------------------------------------------------*/
/*---------------------------------------------------------------*/
/*---------------------------------------------------------------*/
/*---------------------------------------------------------------*/
/*---------------------------------------------------------------*/
/*---------------------------------------------------------------*/
/*---------------------------------------------------------------*/
/*---------------------------------------------------------------*/
/*---------------------------------------------------------------*/
/*---------------------------------------------------------------*/
/*---------------------------------------------------------------*/

