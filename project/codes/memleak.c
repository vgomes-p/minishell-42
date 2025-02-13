int	ft_isdigit(int dig)
{
	if (dig >= '0' && dig <= '9')
		return (1);
	else
		return (0);
}

int	ft_isalnum(int chdig)
{
	if (chdig >= '0' && chdig <= '9')
		return (1);
	if ((chdig >= 'a' && chdig <= 'z')
		|| (chdig >= 'A' && chdig <= 'Z'))
		return (1);
	else
		return (0);
}

char	*ft_strjoin(char const *str0, char const *str1)
{
	char	*nwstr;
	size_t	len0;
	size_t	len1;

	len0 = ft_strlen(str0);
	len1 = ft_strlen(str1);
	nwstr = malloc((len0 + len1 + 1) * sizeof(char));
	if (nwstr == NULL)
		return (NULL);
	ft_strlcpy(nwstr, str0, len0 + 1);
	ft_strlcpy(&nwstr[len0], str1, len1 + 1);
	return (nwstr);
}

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	cnt;

	cnt = 0;
	if (size == 0)
		return (ft_strlen(src));
	while (cnt < (size - 1) && src[cnt])
	{
		dest[cnt] = src[cnt];
		cnt++;
	}
	dest[cnt] = '\0';
	return (ft_strlen(src));
}

size_t	ft_strlen(const char *var)
{
	size_t	cnt;

	cnt = 0;
	while (var[cnt] != '\0')
	{
		cnt++;
	}
	return (cnt);
}

char	*ft_strdup(const char *str0)
{
	int		cnt;
	char	*str1;

	cnt = 0;
	str1 = malloc(ft_strlen(str0) + 1);
	if (!str1)
		return (NULL);
	while (*str0)
		str1[cnt++] = *str0++;
	str1[cnt] = '\0';
	return (str1);
}

void	ft_bzero(void *str, size_t nby)
{
	ft_memset(str, 0, nby);
}

void	*ft_calloc(size_t num_el, size_t numby)
{
	void	*memaloc;
	size_t	finsize;

	memaloc = NULL;
	finsize = num_el * numby;
	if (num_el == 0 || numby == 0 || finsize / num_el != numby)
		return (NULL);
	memaloc = malloc(finsize);
	if (memaloc)
		ft_bzero(memaloc, finsize);
	return (memaloc);
}

char	*ft_strchr(const char *str, int ch)
{
	while (*str && *str != (char)ch)
		str++;
	if ((char)ch == *str)
		return ((char *)str);
	return (0);
}

void	ft_putstr_fd(char *str, int fd)
{
	write(fd, str, ft_strlen(str));
}

int	find_envar(const char *var, char **envp)
{
	char	*findkey;
	int		varlen;
	int		index;
	char	*equal_sign;

	equal_sign = ft_strchr(var, '=');
	if (equal_sign)
		varlen = equal_sign - var;
	else
		varlen = ft_strlen(var);
	findkey = ft_calloc(varlen + 2, sizeof(char));
	ft_strlcpy(findkey, var, varlen + 2);
	findkey[varlen] = '=';
	findkey[varlen + 1] = '\0';
	index = 0;
	while (envp[index] && ft_strncmp(envp[index], findkey, varlen + 1))
		index++;
	free(findkey);
	return (index);
}

void	update_envar(const char *var, int index0, char ***envp)
{
	char	**nwenv;
	int		envsz;
	int		index1;

	envsz = 0;
	while (*envp && (*envp)[envsz])
		envsz++;
	if (index0 < envsz)
	{
		free((*envp)[index0]);
		(*envp)[index0] = ft_strdup(var);
	}
	else
	{
		nwenv = ft_calloc(envsz + 2, sizeof(char *));
		index1 = -1;
		while (++index1 < envsz)
			nwenv[index1] = ft_strdup((*envp)[index1]);
		nwenv[envsz] = ft_strdup(var);
		index1 = -1;
		while (++index1 < envsz)
			free((*envp)[index1]);
		free(*envp);
		*envp = nwenv;
	}
}

void	ms_pwd(t_minishell *shell)
{
	char	*cwd;
	int		pwd_index;
	char	*pwd_env;

	cwd = getcwd(NULL, 0);
	pwd_env = ft_strjoin("PWD=", cwd);
	if (!cwd)
	{
		ft_putstr_fd(RED "pwd: error" RESET, 2);
		return ;
	}
	ft_putstr_fd(cwd, STDOUT_FILENO);
	ft_putstr_fd("\n", STDOUT_FILENO);
	pwd_index = find_envar("PWD", shell->env);
	update_envar(pwd_env, pwd_index, &shell->env);
	free(pwd_env);
	free(cwd);
}

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

char	**dup_env(char **envp, size_t *envsz)
{
	char	**nwenv;
	int		cnt;
	int		pos;

	cnt = 0;
	if (envp)
		while (envp[cnt])
			cnt++;
	*envsz = cnt;
	nwenv = ft_calloc(cnt + 1, sizeof(char *));
	if (!nwenv)
		return (NULL);
	pos = -1;
	while (++pos < cnt)
	{
		nwenv[pos] = ft_strdup(envp[pos]);
		if (!nwenv[pos])
		{
			while (--pos >= 0)
				free(nwenv[pos]);
			free(nwenv);
			return (NULL);
		}
	}
	return (nwenv);
}

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

char	*lms_strstr(const char *haystack, const char *needle)
{
	size_t	h_index;
	size_t	n_index;

	if (*needle == '\0')
		return ((char *)haystack);
	h_index = 0;
	while (haystack[h_index] != '\0')
	{
		n_index = 0;
		while (haystack[h_index + n_index] == needle[n_index]
			&& needle[n_index] != '\0')
			n_index++;
		if (needle[n_index] == '\0')
			return ((char *)(haystack + h_index));
		h_index++;
	}
	return (NULL);
}

char	*lms_strjoin_free(char *str1, char *str2)
{
	char	*joined;

	joined = ft_strjoin(str1, str2);
	free(str1);
	return (joined);
}

void	lms_putstr(char *str)
{
	if (str)
	{
		while (*str)
		{
			write(1, str, 1);
			str++;
		}
	}
}

t_token	*mktoken(char *value, t_token_tp type)
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
			free_split(split);
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
	head = NULL;
	head = create_token_list(split, head);
	if (head)
		free_split(split);
	return (head);
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

void	free_split(char **split)
{
	int	pos;

	pos = 0;
	while (split[pos])
	{
		free(split[pos]);
		pos++;
	}
	free(split);
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
		printf(RED "Error: quotes not closed" RESET);
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

int	main(int argc, char **argv, char **envp)
{
	t_minishell	shell;

	(void)argc;
	(void)argv;
	shell.env = dup_env(envp, &shell.env_size);
	shell.prompt = NULL;
	shell.exit_stt = 0;
	welcome();
	while (1)
	{
		ms_prompt(&shell);
	}
	return (0);
}