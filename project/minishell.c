bool	process_quotes(const char *input, int *pos, bool *in_quotes,
	char *quote_ch)
{
while (input[*pos] && (*in_quotes || input[*pos] != ' '))
{
if (is_quotes(input[*pos]))
{
if (!*in_quotes)
{
*in_quotes = true;
*quote_ch = input[*pos];
}
else if (input[*pos] == *quote_ch)
*in_quotes = false;
}
(*pos)++;
}
if (*in_quotes)
{
printf(RED "Error: quotes not closed\n" RESET);
return (false);
}
return (true);
}

char	**process_tokens(const char *input, char **tokens)
{
char	*token;
int		pos;
int		token_cnt;

pos = 0;
token_cnt = 0;
while (input[pos])
{
while (input[pos] == ' ')
pos++;
if (input[pos] == '\0')
break ;
token = extract_token(input, &pos);
if (token)
tokens[token_cnt++] = token;
else
{
cleanup_tokens(tokens, token_cnt);
return (NULL);
}
}
tokens[token_cnt] = NULL;
return (tokens);
}

char	*extract_token(const char *input, int *pos)
{
int		start;
bool	in_quotes;
char	quote_ch;

start = *pos;
in_quotes = false;
quote_ch = '\0';
if (!process_quotes(input, pos, &in_quotes, &quote_ch))
return (NULL);
return (clean_token(&input[start], *pos - start));
}

t_token_tp	get_token_type(char *token, t_token *current, int is_first)
{
t_token_tp	type;

type = ARG;
if (is_operator(token))
{
if (lms_strcmp(token, "|") == 0)
type = PIPE;
else if (lms_strcmp(token, ">") == 0)
type = REDIR_OUT;
else if (lms_strcmp(token, ">>") == 0)
type = REDIR_APPEND;
else if (lms_strcmp(token, "<") == 0)
type = REDIR_IN;
else if (lms_strcmp(token, "<<") == 0)
type = HEREDOC;
}
else if (is_first || (current && current->type == PIPE))
type = CMD;
return (type);
}

bool	is_quotes(char ch)
{
	return (ch == '\'' || ch == '\"');
}

bool	is_operator(char *str)
{
	return (lms_strcmp(str, "|") == 0 || lms_strcmp(str, ">") == 0
		|| lms_strcmp(str, "<") == 0 || lms_strcmp(str, ">>") == 0
		|| lms_strcmp(str, "<<") == 0);
}

void	cleanup_tokens(char **tokens, int token_cnt)
{
	int	pos;

	pos = 0;
	while (pos < token_cnt)
	{
		free(tokens[pos]);
		pos++;
	}
	free(tokens);
}

int	count_tokens(t_token *tokens)
{
	int		count;
	t_token	*current;

	count = 0;
	current = tokens;
	while (current)
	{
		count++;
		current = current->next;
	}
	return (count);
}

char	*clean_token(const char *str, int len)
{
	char	*cleaned;
	int		pos;
	int		nwpos;

	cleaned = malloc(len + 1);
	pos = 0;
	nwpos = 0;
	if (!cleaned)
		return (NULL);
	while (pos < len)
	{
		if (!is_quotes(str[pos]))
		{
			cleaned[nwpos++] = str[pos];
		}
		pos++;
	}
	cleaned[nwpos] = '\0';
	return (cleaned);
}

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

t_token	*cpy_token_ls(t_token *tokens)
{
	t_token	*new_list;
	t_token	*current;
	t_token	*new_token;

	if (!tokens)
		return (NULL);
	new_list = NULL;
	current = tokens;
	while (current)
	{
		new_token = mktoken(current->value, current->type);
		if (!new_token)
		{
			free_tokens(new_list);
			return (NULL);
		}
		if (!new_list)
			new_list = new_token;
		else
			addtoken_ls(new_list, new_token);
		current = current->next;
	}
	return (new_list);
}

void	addtoken_ls(t_token *list, t_token *new_token)
{
	t_token	*current;

	if (!list || !new_token)
		return ;
	current = list;
	while (current->next)
		current = current->next;
	current->next = new_token;
}

t_token	*mktoken(char *value, t_token_tp type)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->value = ft_strdup(value);
	if (!token->value)
	{
		free(token);
		return (NULL);
	}
	token->type = type;
	token->next = NULL;
	return (token);
}

char	**ms_split_quotes(const char *input)
{
	char	**tokens;

	tokens = ft_calloc(ft_strlen(input) + 1, sizeof(char *));
	if (!tokens)
		return (NULL);
	return (process_tokens(input, tokens));
}

t_token	*create_token_list(char **split, t_token *head)
{
	t_token	*current;
	t_token	*nwtoken;
	int		pos;

	current = NULL;
	pos = 0;
	while (split[pos])
	{
		nwtoken = mktoken(split[pos],
				get_token_type(split[pos], current, pos == 0));
		if (!nwtoken)
		{
			sfree(split);
			free_tokens(head);
			return (NULL);
		}
		if (!head)
			head = nwtoken;
		else
			current->next = nwtoken;
		current = nwtoken;
		pos++;
	}
	return (head);
}

t_token	*tokening(char *input)
{
	char	**split;
	t_token	*head;

	split = ms_split_quotes(input);
	if (!split)
		return (NULL);
	head = create_token_list(split, NULL);
	if (!head)
	{
		sfree(split);
		return (NULL);
	}
	sfree(split);
	return (head);
}

bool	valid_syntax(t_token *tokens)
{
	t_token	*current;

	current = tokens;
	while (current)
	{
		if (current->type == PIPE || current->type == REDIR_OUT
			|| current->type == REDIR_IN || current->type == REDIR_APPEND
			|| current->type == HEREDOC)
		{
			if (!current->next || (current->next->type != ARG
					&& current->next->type != CMD))
			{
				printf(RED "Syntax error: '%s' operator without args.\n" RESET,
					current->value);
				return (false);
			}
		}
		current = current->next;
	}
	return (true);
}

int	parser(t_token **head, char *str)
{
	*head = tokening(str);
	if (!*head)
	{
		ft_putstr_fd(RED "error: unclosed quotes\n" RESET, 2);
		return (1);
	}
	if (!valid_syntax(*head))
	{
		free_tokens(*head);
		*head = NULL;
		return (1);
	}
	return (0);
}

int	is_buildin(char *token)
{
	char	**ls;
	int		pos;

	ls = ft_calloc(8, sizeof(char *));
	if (!ls)
		return (-1);
	ls[0] = ft_strdup("echo");
	ls[1] = ft_strdup("cd");
	ls[2] = ft_strdup("pwd");
	ls[3] = ft_strdup("export");
	ls[4] = ft_strdup("unset");
	ls[5] = ft_strdup("env");
	ls[6] = ft_strdup("exit");
	ls[7] = NULL;
	pos = -1;
	while (ls[++pos])
	{
		if (!ft_strncmp(token, ls[pos], ft_strlen(token)))
		{
			sfree(ls);
			return (1);
		}
	}
	sfree(ls);
	return (0);
}

static void	free_args(char **args, int cnt)
{
	int	pos;

	pos = 0;
	while (pos < cnt)
	{
		free(args[pos]);
		pos++;
	}
	free(args);
}

static t_token	*process_next_token(t_token *current, char **args, int *arg_pos)
{
	if (current->type == REDIR_IN || current->type == REDIR_OUT || 
		current->type == REDIR_APPEND || current->type == HEREDOC)
	{
		current = current->next;
		if (current)
			current = current->next;
	}
	else
	{
		args[*arg_pos] = ft_strdup(current->value);
		if (!args[*arg_pos])
			return (NULL);
		(*arg_pos)++;
		current = current->next;
	}
	return (current);
}

char	**prepare_args(t_token *tokens)
{
	char	**args;
	int		arg_pos;
	t_token	*current;

	if (!tokens)
		return (NULL);
	args = malloc(sizeof(char *) * (count_tokens(tokens) + 1));
	if (!args)
		return (NULL);
	current = tokens;
	arg_pos = 0;
	while (current)
	{
		current = process_next_token(current, args, &arg_pos);
		if (current == NULL && arg_pos > 0)
		{
			free_args(args, arg_pos - 1);
			return (NULL);
		}
	}
	args[arg_pos] = NULL;
	return (args);
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
	rl_clear_history();
	unlink("__heredoc");
	exit(shell->error_code);
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

t_token	*get_next_cmd(t_token **tokens)
{
	t_token	*current;
	t_token	*cmd_start;
	t_token	*prev;

	if (!tokens || !*tokens)
		return (NULL);
	cmd_start = *tokens;
	current = *tokens;
	prev = NULL;
	while (current && current->type != PIPE)
	{
		prev = current;
		current = current->next;
	}
	if (current)
	{
		if (prev)
			prev->next = NULL;
		*tokens = current->next;
	}
	else
		*tokens = NULL;
	return (cmd_start);
}

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

void	file_errmsg(t_minishell *shell, char *cmd)
{
	char	*color_cmd;

	color_cmd = ft_strjoin(RED, cmd);
	ft_putstr_fd(color_cmd, 2);
	free(color_cmd);
	shell->error_code = 1;
}

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
	sfree(path_dir);
	path_dir = NULL;
	return (full_path);
}

static int	check_builtin_type(char **args, t_minishell *shell, int *ret)
{
	*ret = 1;
	if (lms_strcmp(args[0], "cd") == 0)
		ms_cd(args, shell);
	else if (lms_strcmp(args[0], "echo") == 0)
		ms_echo(args);
	else if (lms_strcmp(args[0], "env") == 0)
		ms_env(shell);
	else if (lms_strcmp(args[0], "exit") == 0)
		ms_exit(args, shell);
	else if (lms_strcmp(args[0], "pwd") == 0)
		ms_pwd(shell);
	else if (lms_strcmp(args[0], "export") == 0)
	{
		ms_export(shell, args, &shell->env);
		if (shell->error_code != 0)
			*ret = shell->error_code;
	}
	else if (lms_strcmp(args[0], "unset") == 0)
		ms_unset(shell, args, &shell->env);
	else
		*ret = 0;
	return (*ret);
}

int	exec_builtin(t_token *tokens, t_minishell *shell)
{
	char	**args;
	int		ret;

	args = prepare_args(tokens);
	if (!args)
		return (-1);
	ret = check_builtin_type(args, shell, &ret);
	sfree(args);
	return (ret);
}

void	process_redirections(t_token *current)
{
	while (current)
	{
		if (current->type == REDIR_IN || current->type == REDIR_OUT || 
			current->type == REDIR_APPEND)
			handle_redirects(current);
		else if (current->type == HEREDOC)
			handle_heredoc(current);
		current = current->next;
	}
}

static int	allocate_pid_memory(t_exec *exec)
{
	exec->pid = malloc(sizeof(pid_t) * exec->nbr_pros);
	if (!exec->pid)
		return (0);
	return (1);
}

static void	execute_command(t_minishell *shell, t_exec *exec, 
							t_token *cmd_tokens, int pos)
{
	exec->cmd = tokens_matrix(cmd_tokens);
	exec->pid[pos] = fork();
	if (exec->pid[pos] == 0)
	{
		child(shell, exec->cmd, exec->fd, pos);
	}
	sfree(exec->cmd);
	exec->cmd = NULL;
	free_tokens(cmd_tokens);
}

static void	process_commands(t_minishell *shell, t_exec *exec, 
							t_token **current_tokens)
{
	int		pos;
	t_token	*cmd_tokens;

	pos = -1;
	while (++pos < exec->nbr_pros)
	{
		cmd_tokens = get_next_cmd(current_tokens);
		execute_command(shell, exec, cmd_tokens, pos);
	}
}

void	exec_child(t_minishell *shell, t_exec *exec, int pos)
{
	t_token	*current_tokens;

	(void)pos;
	process_redirections(exec->temp);
	if (!allocate_pid_memory(exec))
		return ;
	current_tokens = shell->tokens;
	process_commands(shell, exec, &current_tokens);
}

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
		if (exec.temp->type == PIPE)
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

int	exec_parent(t_minishell *shell, int nb_pros, char **cmd, int **fd)
{
	int		saved_stdout;
	t_token	*redir_tokens;

	saved_stdout = dup(STDERR_FILENO);
	if (saved_stdout == -1)
	{
		perror("dup");
		return (-1);
	}
	redir_tokens = shell->tokens;
	process_redirections(redir_tokens);
	if (!ft_strncmp(cmd[0], "./", 2) && is_dir(shell, cmd[0]) == 1)
	{
		dup2(saved_stdout, STDOUT_FILENO);
		close(saved_stdout);
		return (0);
	}
	if (nb_pros > 1)
	{
		dup2(saved_stdout, STDOUT_FILENO);
		close(saved_stdout);
		return (-1);
	}
	if (exec_builtin(shell->tokens, shell))
	{
		dup2(saved_stdout, STDOUT_FILENO);
		close(saved_stdout);
		sfree_int(fd);
		fd = NULL;
		return (0);
	}
	dup2(saved_stdout, STDOUT_FILENO);
	close(saved_stdout);
	return (-1);
}

void	cleanup_processes(t_exec *exec, t_minishell *shell, int cmd_pos)
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

void	exec_cmd(t_minishell *shell)
{
	int		cmd_pos;
	t_exec	exec;
	t_token	*tokens_copy;

	if (!shell->tokens || !shell->tokens->value || !*shell->tokens->value)
		return ;
	tokens_copy = cpy_token_ls(shell->tokens);
	exec = init_exec(shell);
	cmd_pos = exec_parent(shell, exec.nbr_pros, exec.cmd, exec.fd);
	if (cmd_pos > 0)
	{
		sfree(exec.cmd);
		exec.cmd = NULL;
	}
	if (cmd_pos == 0)
		return ;
	exec_child(shell, &exec, cmd_pos);
	cleanup_processes(&exec, shell, cmd_pos);
	free_tokens(tokens_copy);
}