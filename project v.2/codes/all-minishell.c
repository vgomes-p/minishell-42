int	count_tokens(t_token *tokens)
{
	int	count;
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

void	free_tokens(t_token *tokens)
{
	t_token	*current;
	t_token	*next;

	current = tokens;
	while (current)
	{
		next = current->next;
		if (current->value)
			free(current->value);
		free(current);
		current = next;
	}
}

static t_token	*mktoken(char *value, t_token_tp type)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->value = ft_strdup(value);
	token->type = type;
	token->next = NULL;
	return (token);
}

static bool	is_operator(char *str)
{
	return (lms_strcmp(str, "|") == 0 || lms_strcmp(str, ">") == 0
		|| lms_strcmp(str, "<") == 0 || lms_strcmp(str, ">>") == 0
		|| lms_strcmp(str, "<<") == 0);
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

t_token	*tokening(char *input)
{
	char	**split;
	t_token	*head;
	t_token	*current;
	t_token	*nwtoken;
	int		index0;
	int		index1;

	split = ms_split_quotes(input);
	if (!split)
		return (NULL);
	head = NULL;
	current = NULL;
	index0 = 0;
	while (split[index0])
	{
		nwtoken = mktoken(split[index0],
				get_token_type(split[index0], current, index0 == 0));
		if (!nwtoken)
		{
			index1 = 0;
			while (split[index1])
			{
				free(split[index1]);
				index1++;
			}
			free(split);
			free_tokens(head);
			return (NULL);
		}
		if (!head)
			head = nwtoken;
		else
			current->next = nwtoken;
		current = nwtoken;
		index0++;
	}
	index1 = 0;
	while (split[index1])
	{
		free(split[index1]);
		index1++;
	}
	free(split);
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

static bool	is_quotes(char ch)
{
	return (ch == '\'' || ch == '\"');
}

static char	*clean_token(const char *str, int len)
{
	char	*cleaned;
	int		index0;
	int		index1;

	cleaned = malloc(len + 1);
	index0 = 0;
	index1 = 0;

	if (!cleaned)
		return (NULL);
	while (index0 < len)
	{
		if (!is_quotes(str[index0]))
		{
			cleaned[index1++] = str[index0];
		}
		index0++;
	}
	cleaned[index1] = '\0';
	return (cleaned);
}

static char	*extract_token(const char *input, int *index)
{
	int		start;
	bool	in_quotes;
	char	quote_ch;

	start = *index;
	in_quotes = false;
	quote_ch = '\0';
	while (input[*index] && (in_quotes || input[*index] != ' '))
	{
		if (is_quotes(input[*index]))
		{
			if (!in_quotes)
			{
				in_quotes = true;
				quote_ch = input[*index];
			}
			else if (input[*index] == quote_ch)
			{
				in_quotes = false;
			}
		}
		(*index)++;
	}
	if (in_quotes)
	{
		printf(RED "Error: quotes not closed" RESET);
		return (NULL);
	}
	return (clean_token(&input[start], *index - start));
}

char	**ms_split_quotes(const char *input)
{
	char	**tokens;
	char	*token;
	int		index0;
	int		token_cnt;
	int		index1;

	index0 = 0;
	token_cnt = 0;
	tokens = ft_calloc(ft_strlen(input) + 1, sizeof(char *));
	if (!tokens)
		return (NULL);
	while (input[index0])
	{
		while (input[index0] == ' ')
			index0++;
		if (input[index0] == '\0')
			break ;
		token = extract_token(input, &index0);
		if (token)
		{
			tokens[token_cnt++] = token;
		}
		else
		{
			index1 = 0;
			while (index1 < token_cnt)
			{
				free(tokens[index1]);
				index1++;
			}
			free(tokens);
			return (NULL);
		}
	}
	tokens[token_cnt] = NULL;
	return (tokens);
}

void	ms_cd(char **args)
{
	char	*home;

	if (!args[1])
	{
		home = getenv("HOME");
		if (home)
			chdir(home);
		else
			ft_putstr_fd("cd: " RED "HOME not set" RESET, 2);
	}
	else
	{
		if (chdir(args[1]) == -1)
			perror("cd");
	}
}

void	ms_echo(char **args)
{
	int	index;
	int	nwline;

	index = 1;
	nwline = 1;
	if (args[1] && lms_strcmp(args[1], "-n") == 0)
	{
		nwline = 0;
		index++;
	}
	while (args[index])
	{
		lms_putstr(args[index]);
		if (args[index + 1])
			lms_putstr(" ");
		index++;
	}
	if (nwline)
		lms_putstr("\n");
}

extern char	**environ;

void	ms_env(void)
{
	int	index;

	index = 0;
	while (environ[index])
	{
		lms_putstr(environ[index]);
		lms_putstr("\n");
		index++;
	}
}

void	ms_exit(char **args, t_minishell *shell)
{
	int	stat;

	stat = 0;
	if (args[1])
		stat = ft_atoi(args[1]);
	shell->exit_stt = stat;
	free(shell->prompt);
	exit(stat);
}

static void	display_environment(char **env)
{
	int	index;

	index = 0;
	while (env[index])
	{
		lms_putstr(env[index]);
		lms_putstr("\n");
		index++;
	}
}

static int	handle_variable_assignment(char ***env, char *arg)
{
	char	*equal_sign;

	equal_sign = ft_strchr(arg, '=');
	if (!equal_sign)
		return (0);
	*equal_sign = '\0';
	if (lms_setenv(env, arg, equal_sign + 1, 1) == -1)
	{
		ft_putstr_fd("export: " RED "merror setting variable" RESET, 2);
		*equal_sign = '=';
		return (-1);
	}
	*equal_sign = '=';
	return (1);
}

void	ms_export(char ***env, char **args)
{
	if (!args[1])
	{
		ft_putstr_fd("export: not enough args\nusage: export VAR=VALUE\n", 2);
		return ;
	}
	if (handle_variable_assignment(env, args[1]) == 0)
		display_environment(*env);
}

void	ms_pwd(void)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (cwd)
	{
		lms_putstr(cwd);
		lms_putstr("\n");
		free(cwd);
	}
	else
		ft_putstr_fd("pwd: " RED "error" RESET, 2);
}

void	ms_unset(char ***env, char **args)
{
	if (args[1])
	{
		if (lms_unsetenv(env, args[1]) == -1)
			ft_putstr_fd("unset: " RED "error unsetting variable\n" RESET, 2);
	}
	else
		ft_putstr_fd("unset: not enough args\nusage: unset VAR\n", 2);
}

void	exec_extern(t_token *tokens, t_minishell *shell)
{
	char	**args;
	pid_t	pid;
	int		index0;
	t_token	*current;

	args = malloc(sizeof(char *) * (count_tokens(tokens) + 1));
	if (!args)
		return ;
	current = tokens;
	index0 = 0;
	while (current)
	{
		args[index0++] = current->value;
		current = current->next;
	}
	args[index0] = NULL;
	pid = fork();
	if (pid == 0)
	{
		if (execve(args[0], args, shell->env) == -1)
		{
			perror(RED "execve" RESET);
			exit(EXIT_FAILURE);
		}
	}
	else if (pid < 0)
		perror(RED "fork" RESET);
	else
		waitpid(pid, NULL, 0);/*colocar WNOHANG no lugar do 0 se der timeout*/
	free(args);
}

int	exec_builtin(t_token *tokens, t_minishell *shell)
{
	char	**args;
	t_token	*current;
	int		index0;

	current = tokens;
	args = malloc(sizeof(char *) * (count_tokens(tokens) + 1));
	if (!args)
		return (-1);
	index0 = 0;
	while (current)
	{
		args[index0++] = current->value;
		current = current->next;
	}
	args[index0] = NULL;

	if (lms_strcmp(args[0], "cd") == 0)
		ms_cd(args);
	else if (lms_strcmp(args[0], "echo") == 0)
		ms_echo(args);
	else if (lms_strcmp(args[0], "env") == 0)
		ms_env();
	else if (lms_strcmp(args[0], "exit") == 0)
		ms_exit(args, shell);
	else if (lms_strcmp(args[0], "export") == 0)
		ms_export(&(shell->env), args);
	else if (lms_strcmp(args[0], "pwd") == 0)
		ms_pwd();
	else if (lms_strcmp(args[0], "unset") == 0)
		ms_unset(&(shell->env), args);
	else
	{
		free(args);
		return (0);
	}
	free(args);
	return (1);
}

static char	*pathedprompt(t_minishell *shell)
{
	(void)shell;
	char	*cwd;
	char	*home;
	char	*relative_cwd;
	char	*prompt;

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
	prompt = lms_strjoin_free(prompt, CYAN " minishell$ " RESET);
	free(cwd);
	return (prompt);
}

void	welcome(void)
{
	lms_putstr("                         ");
	lms_putstr(RECYAN "{Made by vgomes-p & sthrodri}" RESET "\n\n");
	lms_putstr("\n" CYAN "╔═════════════════════════════════════");
	lms_putstr("═════════════════════════════════════════╗\n");
	lms_putstr("║                            WELCOME T");
	lms_putstr("O MINISHELL                              ║\n");
	lms_putstr("╚══════════════════════════════════════");
	lms_putstr("════════════════════════════════════════╝" RESET "\n");
}

void	ms_prompt(t_minishell *shell)
{
	char	*input;
	t_token	*tokens;
	char	*prompt;

	prompt = pathedprompt(shell);
	if (!prompt)
	{
		ft_putstr_fd(RED "Error: Failed to generate prompt\n" RESET, 2);
		return ;
	}
	input = readline(prompt);
	free(prompt);
	if (!input)
	{
		ft_putstr_fd(RED "\nSee you soon, goodbye!\n" RESET, 1);
		free(shell->prompt);
		exit(shell->exit_stt);
	}
	if (input[0] == '\0')
	{
		free(input);
		return ;
	}
	shell->prompt = input;
	tokens = tokening(input);
	if (!tokens)
	{
		ft_putstr_fd(RED "Error: Tokenination has failed\n" RESET, 2);
		return ;
	}
	if (!valid_syntax(tokens))
	{
		ft_putstr_fd(RED "Syntax error\n" RESET, 2);
		free_tokens(tokens);
		return ;
	}
	if (exec_builtin(tokens, shell) == 0)
		exec_extern(tokens, shell);
	free(input);
	free_tokens(tokens);
	rl_clear_history();
}

int	main(int argc, char **argv, char **envp)
{
	t_minishell	shell;

	(void)argc;
	(void)argv;
	shell.env = envp;
	shell.prompt = NULL;
	shell.exit_stt = 0;
	welcome();
	while (1)
	{
		ms_prompt(&shell);
	}
	return (0);
}
