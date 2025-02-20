void	free_env(char **env)
{
	int	pos;

	if(!env)
		return ;
	pos = 0;
	while (env[pos])
	{
		free(env[pos]);
		pos++;
	}
	free(env);
}
void	free_tokens(t_token *tokens)
{
	t_token	*current;
	t_token	*next;

	current = tokens;
	while (current)
	{
		next = current->next;
		free(current->value);
		free(current);
		current = next;
	}
}

void	sfree(char **split)
{
	int	pos;

	if (!split)
		return ;
	pos = 0;
	while (split[pos])
	{
		free(split[pos]);
		pos++;
	}
	free(split);
}

char	*free_ptr(char *ptr)
{
	free(ptr);
	ptr = NULL;
	return (NULL);
}

void	sfree_int(int **fd)
{
	int	pos;

	if (!fd)
		return;
	pos = 0;
	while (fd[pos])
	{
		free(fd[pos]);
		pos++;
	}
	free(fd);
}

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
		args[arg_pos] = ft_strdup(current->value);
		if (!args[arg_pos])
		{
			free_args(args, arg_pos);
			return (NULL);
		}
		arg_pos++;
		current = current->next;
	}
	args[arg_pos] = NULL;
	return (args);
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

static char	*pathedprompt(t_minishell *shell)
{
	char	*cwd;
	char	*home;
	char	*relative_cwd;
	char	*prompt;

	(void)shell;
	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		perror("getcwd");
		return (NULL);
	}
	home = getenv("HOME");
	if (home && lms_strstr(cwd, home) == cwd)
	{
		relative_cwd = ft_strjoin("~", cwd + ft_strlen(home));
		free(cwd);
		cwd = relative_cwd;
	}
	prompt = ft_strjoin(GREEN, cwd);
	prompt = lms_strjoin_free(prompt, RESET);
	prompt = lms_strjoin_free(prompt, CYAN " minishell$ > " RESET);
	free(cwd);
	return (prompt);
}

void	welcome(void)
{
	lms_putstr(CYAN "╔═════════════════════════════════════");
	lms_putstr("═════════════════════════════════════════╗\n");
	lms_putstr("║                            WELCOME T");
	lms_putstr("O MINISHELL                              ║\n");
	lms_putstr("╚══════════════════════════════════════");
	lms_putstr("════════════════════════════════════════╝" RESET "\n");
}

static void	handle_input(t_minishell *shell, char **input)
{
	char	*prompt;

	prompt = pathedprompt(shell);
	if (!prompt)
	{
		ft_putstr_fd(RED "Error: Failed to generate prompt\n" RESET, 2);
		return ;
	}
	*input = readline(prompt);
	free(prompt);
	if (!*input)
	{
		ft_putstr_fd(RECYAN "\n\n\nSee you soon, goodbye!\n\n\n" RESET, 1);
		free(shell->prompt);
		free_env(shell->env);
		rl_clear_history();
		exit(shell->exit_stt);
	}
	if ((*input)[0] == '\0')
	{
		free(*input);
		*input = NULL;
		return ;
	}
	add_history(*input);
}

static void	process_command(char *input, t_minishell *shell)
{
	t_token	*tokens;

	tokens = tokening(input);
	if (!tokens)
	{
		ft_putstr_fd(RED "Error: Tokenination has failed\n" RESET, 2);
		free(input);
		return ;
	}
	if (!valid_syntax(tokens))
	{
		ft_putstr_fd(RED "Syntax error\n" RESET, 2);
		free_tokens(tokens);
		free(input);
		return ;
	}
	if (exec_builtin(tokens, shell) == 0)
		exec_extern(tokens, shell);
	free_tokens(tokens);
	free(input);
}

void	ms_prompt(t_minishell *shell)
{
	char	*input;

	handle_input(shell, &input);
	if (input)
		process_command(input, shell);
}

char	**dup_env(char **envp, size_t *envsz)
{
	char	**nwenv;
	size_t		cnt;
	size_t		pos;

	if (!envp || !envsz)
		return (NULL);
	cnt = 0;
	while (envp[cnt])
		cnt++;
	*envsz = cnt;
	nwenv = ft_calloc(cnt + 1, sizeof(char *));
	if (!nwenv)
		return (NULL);
	pos = 0;
	while (pos < cnt)
	{
		nwenv[pos] = ft_strdup(envp[pos]);
		if (!nwenv[pos])
		{
			while (--pos > 0)
				free(nwenv[--pos]);
			free(nwenv);
			return (NULL);
		}
		pos++;
	}
	nwenv[cnt] = NULL;
	return (nwenv);
}

void	handle_signal(int sig)
{
	(void)sig;
	if (g_shell->env)
	{
		free_env(g_shell->env);
		g_shell->env = NULL;
	}
	exit(0);
}

t_minishell	*g_shell = NULL;

int	main(int argc, char **argv, char **envp)
{
	t_minishell	shell;

	(void)argc;
	(void)argv;
	shell.env = dup_env(envp, &shell.env_size);
	shell.prompt = NULL;
	shell.exit_stt = 0;
	g_shell = &shell;
	signal(SIGINT, handle_signal);
	signal(SIGQUIT, handle_signal);
	welcome();
	while (1)
	{
		ms_prompt(&shell);
	}
	free_env(shell.env);
	return (0);
}