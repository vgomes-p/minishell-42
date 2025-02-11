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

void	free_split_array(char **split)
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
			free_split_array(split);
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
		free_split_array(split);
	return (head);
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

char	**ms_split_quotes(const char *input)
{
	char	**tokens;

	tokens = ft_calloc(ft_strlen(input) + 1, sizeof(char *));
	if (!tokens)
		return (NULL);
	return (process_tokens(input, tokens));
}