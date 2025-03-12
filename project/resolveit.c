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

static int	alloc_token_str(char **ret, t_token *token, int cnt)
{
	int	pos;

	pos = 0;
	while (pos < cnt)
	{
		ret[pos] = ft_strdup(token->value);
		if (!ret[pos])
		{
			while (--pos >= 0)
				free(ret[pos]);
			free(ret);
			return (0);
		}
		token = token->next;
		pos++;
	}
	ret[pos] = NULL;
	return (1);
}

char	**tokens_matrix(t_token *token)
{
	int		cnt;
	char	**ret;

	if (!token)
		return (NULL);
	cnt = count_tokens(token);
	ret = ft_calloc((cnt + 1), sizeof(char *));
	if (!ret)
		return (NULL);
	if (!alloc_token_str(ret, token, cnt))
		return (NULL);
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
		free(token->value);
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
	sfree(split);
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

static void	handle_quoted_part(char *str, char *result, int *ind0, int *ind1)
{
	result[(*ind1)++] = str[(*ind0)++];
	while (str[*ind0] && str[*ind0] != '\'')
		result[(*ind1)++] = str[(*ind0)++];
	if (str[*ind0])
		result[(*ind1)++] = str[(*ind0)++];
}

static char	*extract_var_name(char *str, int *ind0)
{
	char	*var_start;
	char	*var_end;
	char	*var_name;

	var_start = &str[*ind0];
	while (str[*ind0] && (ft_isalnum(str[*ind0]) || str[*ind0] == '_'))
		(*ind0)++;
	var_end = &str[*ind0];
	var_name = ft_substr(var_start, 0, var_end - var_start);
	return (var_name);
}

static char	*get_var_value(t_minishell *shell, char *var_name)
{
	char	*var_value;

	if (lms_strcmp(var_name, "?") == 0)
	{
		var_value = ft_itoa(shell->exit_stt);
		if (!var_value)
			var_value = ft_strdup("0");
	}
	else
	{
		var_value = getenv(var_name);
		if (!var_value)
			var_value = ft_strdup("");
		else
			var_value = ft_strdup(var_value);
	}
	return (var_value);
}

static void	handle_var(t_minishell *shell, char *str, char *result,
					int *indices)
{
	char	*var_name;
	char	*var_value;
	int		*ind0;
	int		*ind1;

	ind0 = &indices[0];
	ind1 = &indices[1];
	(*ind0)++;
	var_name = extract_var_name(str, ind0);
	var_value = get_var_value(shell, var_name);
	ft_strlcat(result, var_value, ft_strlen(result)
		+ ft_strlen(var_value) + 1);
	*ind1 += ft_strlen(var_value);
	free(var_name);
	free(var_value);
}

char	*expand_var(t_minishell *shell, char *str)
{
	char	*result;
	int		indices[2];

	indices[0] = 0;
	indices[1] = 0;
	result = ft_calloc(ft_strlen(str) + 1024, sizeof(char));
	if (!result)
		return (str);
	while (str[indices[0]])
	{
		if (str[indices[0]] == '\'' && !strchr(&str[indices[0] + 1], '\''))
			handle_quoted_part(str, result, &indices[0], &indices[1]);
		else if (str[indices[0]] == '$' && str[indices[0] + 1]
			&& str[indices[0] + 1] != ' ')
			handle_var(shell, str, result, indices);
		else
			result[indices[1]++] = str[indices[0]++];
	}
	free(str);
	return (result);
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

static int	pre_process_tks(char *input, t_minishell *shell)
{
	shell->tokens = tokening(input);
	if (!shell->tokens)
	{
		ft_putstr_fd(RED "Error: Tokenination has failed\n" RESET, 2);
		free(input);
		return (0);
	}
	if (!valid_syntax(shell->tokens))
	{
		ft_putstr_fd(RED "Syntax error\n" RESET, 2);
		free_tokens(shell->tokens);
		shell->tokens = NULL;
		free(input);
		return (0);
	}
	return (1);
}

static void	process_command(char *input, t_minishell *shell)
{
	t_token	*current;

	if (!pre_process_tks(input, shell))
		return ;
	current = shell->tokens;
	while (current)
	{
		if (current->type == CMD || current->type == ARG)
			current->value = expand_var(shell, current->value);
		current = current->next;
	}
	exec_cmd(shell);
	free_tokens(shell->tokens);
	shell->tokens = NULL;
	free(input);
}

void	ms_prompt(t_minishell *shell)
{
	char	*input;

	handle_input(shell, &input);
	if (input)
		process_command(input, shell);
}