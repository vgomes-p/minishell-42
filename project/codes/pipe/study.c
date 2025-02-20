/*build absolute cmd path - path handling*/
// static char	*set_right_path(char *cmd, char **paths)
// {
// 	int		i;
// 	char	*ret;
// 	char	*temp;

// 	i = -1;
// 	ret = NULL;
// 	while (paths && paths[++i])
// 	{
// 		temp = ft_strjoin(paths[i], "/");
// 		ret = ft_strjoin(temp, cmd);
// 		temp = free_ptr(temp);
// 		if ((!access(ret, F_OK)) && !access(ret, X_OK))
// 			break ;
// 		ret = free_ptr(ret);
// 	}
// 	return (ret);
// }
// /*look cmd in system*/
// char	*find_path(char	*cmd, char **envp)
// {
// 	int		i;
// 	char	**paths;
// 	char	*rigth_path;

// 	if (cmd[0] == '/' || cmd[0] == '.')
// 	{
// 		if ((!access(cmd, F_OK)) && !access(cmd, X_OK) \
// 		&& ft_strlen(cmd) > 2)
// 			return (cmd);
// 		return (NULL);
// 	}
// 	i = -1;
// 	while (envp && envp[++i])
// 	{
// 		if (!ft_strncmp("PATH=", envp[i], 5))
// 			break ;
// 	}
// 	if (envp[i] == NULL)
// 		return (NULL);
// 	paths = ft_split(envp[i] + 5, ':');
// 	rigth_path = set_right_path(cmd, paths);
// 	paths = free_mat(paths);
// 	return (rigth_path);
// }

/*************************/

/*exec externs*/
// static void	run_scmd(char **cmd, char **envp)
// {
// 	char	*path;
// 	char	*error;
// 	int		i;

// 	i = 3;
// 	while (!close(i))
// 		i++;
// 	path = find_path(cmd[0], envp);
// 	if (!path)
// 	{
// 		error = ft_strjoin(PROMPT_MSG, cmd[0]);
// 		ft_putstr_fd(error, 2);
// 		ft_putstr_fd(": No such file or directory\n", 2);
// 		error = free_ptr (error);
// 		cmd = free_mat(cmd);
// 		return ;
// 	}
// 	execve(path, cmd, envp);
// 	path = free_ptr(path);
// 	error = ft_strjoin(PROMPT_MSG": ", cmd[0]);
// 	perror(error);
// 	error = free_ptr(error);
// }
// /*clean child resources*/
// static void	exit_child(t_mini *ms, char **cmd, int **fd, int code)
// {
// 	int	i;

// 	ms->error = code;
// 	ms->input = free_ptr(ms->input);
// 	ms->prompt = free_ptr(ms->prompt);
// 	ms->token = free_token(ms->token);
// 	ms->envp = free_mat(ms->envp);
// 	cmd = free_mat(cmd);
// 	i = -1;
// 	if (fd)
// 	{
// 		while (fd[++i])
// 			fd[i] = (int *) free_ptr((char *) fd[i]);
// 		fd = (int **) free_mat((char **) fd);
// 	}
// 	rl_clear_history();
// 	unlink("__heredoc");
// 	exit(ms->error);
// }

// static void	file_error_message(t_mini *ms, char *cmd)
// {
// 	ft_putstr_fd(cmd, 2);
// 	ms->error = 1;
// }

// static void	handle_invalid_file(t_mini *ms)
// {
// 	t_token	*temp;

// 	temp = ms->token;
// 	while (temp)
// 	{
// 		if (temp->type == HEREDOC)
// 			ms->error = 0;
// 		if (temp->type == ARG_FILE)
// 		{
// 			if (access(temp->cmd, F_OK))
// 			{
// 				file_error_message(ms, temp->cmd);
// 				ft_putstr_fd(": No such file or directory\n", 2);
// 			}
// 			else if (access(temp->cmd, R_OK) || access(temp->cmd, W_OK))
// 			{
// 				file_error_message(ms, temp->cmd);
// 				ft_putstr_fd(": Permission Denied\n", 2);
// 				ms->error = 1;
// 			}
// 		}
// 		temp = temp->next;
// 	}
// }

// void	child(t_mini *ms, char **cmd, int **fd, int i)
// {
// 	int	out;
// 	int	in;

// 	out = 0;
// 	in = 0;
// 	cmd = redirect(ms, cmd, &out, &in);
// 	if (!cmd || *cmd == NULL)
// 	{
// 		handle_invalid_file(ms);
// 		free_mat(cmd);
// 		exit_child(ms, NULL, fd, ms->error);
// 	}
// 	if (i && !in)
// 		dup2(fd[i - 1][0], 0);
// 	if (fd[i] && !out)
// 		dup2(fd[i][1], 1);
// 	close_fds(fd);
// 	run_scmd(cmd, ms->envp);
// 	exit_child(ms, cmd, fd, ms -> error);
// }


/**************/


// char	**token_to_mat(t_token *token)
// {
// 	int		i;
// 	int		j;
// 	char	**ret;
// 	t_token	*temp;

// 	temp = token;
// 	i = 0;
// 	while (temp && temp->type != PIPE)
// 	{
// 		i++;
// 		temp = temp->next;
// 	}
// 	ret = ft_calloc((i + 1), sizeof(char *));
// 	if (!ret)
// 		return (NULL);
// 	j = -1;
// 	while (++j < i)
// 	{
// 		ret[j] = ft_strdup(token->cmd);
// 		token = token->next;
// 	}
// 	ret[j] = NULL;
// 	return (ret);
// }

// void	close_fds(int **fd)
// {
// 	int	i;

// 	i = 0;
// 	while (fd[i])
// 	{
// 		close(fd[i][0]);
// 		close(fd[i][1]);
// 		i++;
// 	}
// }

/********************************/

/*prepare pipeline executions*/
// static t_executor	init_executor(t_mini *ms)
// {
// 	int			i;
// 	t_executor	ex;

// 	ex.pid = 0;
// 	ex.status = 0;
// 	ex.n_pros = 1;
// 	ex.temp = ms->token;
// 	ex.cmd = token_to_mat(ex.temp);
// 	while (ex.temp)
// 	{
// 		if (ex.temp->type == PIPE)
// 			ex.n_pros++;
// 		ex.temp = ex.temp->next;
// 	}
// 	ex.fd = ft_calloc(ex.n_pros, sizeof(int *));
// 	i = -1;
// 	while (++i < (ex.n_pros - 1))
// 		ex.fd[i] = ft_calloc(2, sizeof(int));
// 	i = -1;
// 	while (++i < (ex.n_pros - 1))
// 		pipe(ex.fd[i]);
// 	ex.temp = ms->token;
// 	return (ex);
// }

// int	is_directory(t_mini *ms, char *cmd)
// {
// 	struct stat		file_info;

// 	(void)ms;
// 	if (stat(cmd, &file_info) != 0)
// 		return (-1);
// 	if (S_ISDIR(file_info.st_mode) == 1)
// 	{
// 		ft_putstr_fd(PROMPT_MSG, 2);
// 		ft_putstr_fd(cmd, 2);
// 		ft_putstr_fd(": this a directory\n", 2);
// 		ms->error = 126;
// 		return (1);
// 	}
// 	return (0);
// }

// static int	exec_on_parent(t_mini *ms, int n_pros, char **cmd, int **fd)
// {
// 	if (!ft_strncmp(cmd[0], "./", 2) && is_directory(ms, cmd[0]) == 1)
// 		return (0);
// 	if (n_pros > 1)
// 		return (-1);
// 	if (builtins(ms, &ms->envp, cmd))
// 	{
// 		fd = (int **)free_mat((char **) fd);
// 		return (0);
// 	}
// 	return (-1);
// }

// static void	exec_on_child(t_mini *ms, t_executor *ex, int i)
// {
// 	ex->pid = malloc(sizeof(pid_t) * ex->n_pros);
// 	while (++i < ex->n_pros)
// 	{
// 		if (i)
// 			ex->cmd = token_to_mat(ex->temp);
// 		ex->pid[i] = fork();
// 		if (ex->pid[i] == 0)
// 			child(ms, ex->cmd, ex->fd, i);
// 		while (ex->temp && ex->temp->type != PIPE)
// 			ex->temp = ex->temp->next;
// 		if (ex->temp && ex->temp->type == PIPE)
// 			ex->temp = ex->temp->next;
// 		ex->cmd = free_mat(ex->cmd);
// 	}
// }

/*exec pipeline cmds*/
// void	executor(t_mini *ms)
// {
// 	int			i;
// 	int			j;
// 	t_executor	ex;

// 	if (!ms->token || !ms->token->cmd || !*ms->token->cmd)
// 		return ;
// 	ex = init_executor(ms);
// 	i = exec_on_parent(ms, ex.n_pros, ex.cmd, ex.fd);
// 	if (i > 0)
// 		ex.cmd = free_mat(ex.cmd);
// 	if (i == 0)
// 		return ;
// 	exec_on_child(ms, &ex, i);
// 	close_fds(ex.fd);
// 	j = -1;
// 	while (ex.fd[++j])
// 		ex.fd[j] = (int *) free_ptr((char *) ex.fd[j]);
// 	ex.fd = (int **) free_mat((char **) ex.fd);
// 	j = -1;
// 	while (++j < ex.n_pros)
// 		waitpid(ex.pid[j], &ex.status, 0);
// 	if (WIFEXITED(ex.status) && i != ex.n_pros)
// 		ms->error = WEXITSTATUS(ex.status);
// 	free(ex.pid);
// }

/*************************/

static char	*ft_strjoin_gnl(char *s1, char *s2)
{
	char	*str;
	size_t	i;
	size_t	j;

	if (!s1)
		s1 = ft_calloc(1, sizeof(char));
	if (!s1 || !s2)
		return (NULL);
	str = ft_calloc(ft_strlen(s1) + ft_strlen(s2) + 1, sizeof (char));
	if (!str)
		return (0);
	i = -1;
	j = 0;
	while (s1[++i])
		str[i] = s1[i];
	while (s2[j])
		str[i++] = s2[j++];
	str[i] = '\0';
	s2 = free_ptr(s2);
	s1 = free_ptr(s1);
	return (str);
}

static char	*exit_status(t_mini *ms, char *f, char *cmd)
{
	char	*ret;

	ret = NULL;
	if (!*cmd)
	{
		f = free_ptr(f);
		return (ft_strdup("$"));
	}
	if (cmd && cmd[0])
		ret = ft_strdup(++cmd);
	f = free_ptr(f);
	return (ft_strjoin_gnl(ft_itoa(ms->error), ret));
}

char	*get_envp(t_mini *ms, char *cmd, char **envp)
{
	char	*ret;
	int		len;
	int		var_len;

	ret = cmd;
	cmd++;
	if (*cmd == '{')
		len = ft_strlen(++cmd);
	else
		len = ft_strlen(cmd);
	if (*cmd == '?' || len == 0)
		return (exit_status(ms, ret, cmd));
	while (*envp)
	{
		var_len = ft_findchr(*envp, '=');
		if (!ft_strncmp(cmd, *envp, var_len))
		{
			ret = free_ptr(ret);
			return (ft_strdup(*envp + len + 1));
		}
		envp++;
	}
	ret = free_ptr(ret);
	return (ft_strdup(""));
}

/*************************************/

static t_expand	init_expantion(t_mini *ms, char *cmd, char **envp, t_expand exp)
{
	while (cmd[++exp.end])
	{
		exp.quotes = check_quotes(cmd[exp.end], exp.quotes);
		if (cmd[exp.end] == '$' && exp.quotes != 2)
		{
			exp.hold_str[exp.ex++] = ft_substr(cmd, exp.start, exp.end - \
			exp.start);
			exp.start = exp.end;
		}
		else if (cmd[exp.start] == '$' && cmd[exp.end] != '{' && \
		!ft_isalnum(cmd[exp.end]) && cmd[exp.end] != '?' \
		&& cmd[exp.end] != '_')
		{
			exp.hold_str[exp.ex++] = get_envp(ms, ft_substr(cmd, exp.start, \
			exp.end - exp.start), envp);
			if (cmd[exp.end] == '}' && cmd[exp.start + 1] == '{' \
			&& cmd[exp.end + 1])
				exp.end++;
			exp.start = exp.end;
		}
	}
	return (exp);
}

static char	*expand_quotes(char *cmd)
{
	int		i;
	int		quotes;
	char	**ret;

	i = -1;
	quotes = 0;
	while (cmd[++i])
	{
		quotes = check_quotes(cmd[i], quotes);
		if ((cmd[i] == '\'' || cmd[i] == '\"') && !quotes)
			cmd[i] = SEP;
		else if ((cmd[i] == '\'' && quotes == 2) || \
		(cmd[i] == '\"' && quotes == 1))
			cmd[i] = SEP;
	}
	ret = ft_split(cmd, SEP);
	if (!*ret)
	{
		ret = free_mat(ret);
		return (ft_strdup(""));
	}
	return (ft_mattstr_copy(ret));
}

int	is_env_directory(t_mini *ms, char *cmd, char **envp)
{
	char			*ret;
	struct stat		file_info;
	char			*temp;

	temp = ft_strdup(cmd);
	ret = get_envp(ms, temp, envp);
	stat(ret, &file_info);
	if (S_ISDIR(file_info.st_mode) == 1)
	{
		return (1);
	}
	return (0);
}

char	*expand(t_mini *ms, char *cmd, char **envp)
{
	t_expand	exp;

	ft_bzero(&exp, sizeof(t_expand));
	while (cmd[exp.i])
		exp.ex_n += 1 * (cmd[exp.i++] == '$');
	exp.ex = (exp.ex_n * 2) + 2;
	exp.hold_str = ft_calloc(exp.ex, sizeof(char *));
	if (!exp.hold_str)
		return (NULL);
	exp.ex = 0;
	exp.end = -1;
	exp = init_expantion(ms, cmd, envp, exp);
	if (cmd[exp.start] == '$')
		exp.hold_str[exp.ex++] = get_envp(ms, ft_substr(cmd, exp.start, \
		exp.end - exp.start), envp);
	else
		exp.hold_str[exp.ex++] = ft_substr(cmd, exp.start, exp.end - exp.start);
	return (ft_mattstr_copy(exp.hold_str));
}
/*expand var in tokens*/
void	expander(t_mini *ms, t_token **head, char **envp)
{
	char	*temp;
	t_token	*token;

	token = *head;
	if (is_env_directory(ms, token->cmd, envp) == 1)
		return ;
	while (token)
	{
		if (ft_strchr(token->cmd, '$'))
		{
			temp = token->cmd;
			token->cmd = expand(ms, token->cmd, envp);
			if (token->cmd == NULL)
				token->cmd = temp;
			else
				temp = free_ptr(temp);
		}
		if (!token->prev || (token->prev && token->prev->type != HEREDOC))
		{
			temp = token->cmd;
			token->cmd = expand_quotes(token->cmd);
			temp = free_ptr(temp);
		}
		token = token->next;
	}
}

/**********************************************/

static int	heredoc(t_mini *ms, const char *eof, char **envp)
{
	char	*input;
	int		file;

	input = NULL;
	file = open("__heredoc", O_WRONLY | O_CREAT | O_EXCL | O_TRUNC, 0600);
	while (1)
	{
		input = readline("> ");
		if (!ft_strncmp(eof, input, ft_strlen(input)))
		{
			input = free_ptr(input);
			break ;
		}
		if (*eof != '\'' && *eof != '\"' && ft_strchr(input, '$'))
			input = expand(ms, input, envp);
		write(file, input, ft_strlen(input));
		write(file, "\n", 1);
		input = free_ptr(input);
		input = NULL;
	}
	close(file);
	file = open("__heredoc", O_RDONLY);
	return (file);
}

/*****************************************************/

static int	is_redin(t_mini *ms, char **cmd, int i, char **envp)
{
	static int	file = -1;

	if (!ft_strncmp(cmd[i], "<", 2))
	{
		file = open(cmd[i + 1], O_RDONLY);
		if (file == -1)
			return (-5);
	}
	else if (!ft_strncmp(cmd[i], "<<", 3))
		file = heredoc(ms, cmd[i + 1], envp);
	return (file);
}

static int	is_redout(char **cmd, int i)
{
	static int	file = -1;

	if (!ft_strncmp(cmd[i], ">", 2))
	{
		file = open(cmd[i + 1], O_WRONLY | O_CREAT, 0777);
		if (file == -1)
			return (-5);
	}
	else if (!ft_strncmp(cmd[i], ">>", 3))
	{
		file = open(cmd[i + 1], O_APPEND | O_WRONLY | O_CREAT, 0777);
		if (file == -1)
			return (-5);
	}
	return (file);
}

static int	is_redirect(char *cmd)
{
	if (!ft_strncmp(cmd, ">", 2))
		return (1);
	if (!ft_strncmp(cmd, ">>", 3))
		return (1);
	if (!ft_strncmp(cmd, "<", 2))
		return (1);
	if (!ft_strncmp(cmd, "<<", 3))
		return (1);
	return (0);
}

void	set_redirect(t_mini *ms, char **cmd, int *fd, char **ret)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (cmd[i])
	{
		if (is_redirect(cmd[i]))
		{
			fd[0] = is_redin(ms, cmd, i, ms->envp);
			fd[1] = is_redout(cmd, i);
			i = i + 2;
			if (fd[0] == -5 || fd[1] == -5)
				break ;
		}
		else
			ret[j++] = ft_strdup(cmd[i++]);
	}
	if (cmd)
	{
		free_mat(cmd);
		cmd = NULL;
	}
}

static void	init_fd(int *fd)
{
	fd[0] = -1;
	fd[1] = -1;
}

char	**redirect(t_mini *ms, char **cmd, int *out, int *in)
{
	int		fd[2];
	char	**ret;
	int		i;

	init_fd(fd);
	i = 0;
	while (cmd[i])
		i++;
	ret = ft_calloc(i + 1, sizeof(char *));
	set_redirect(ms, cmd, fd, ret);
	if (fd[0] == -5 || fd[1] == -5)
		return (free_mat(ret));
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