int	ft_atoi(const char *str)
{
	int	sign;
	int	result;

	result = 0;
	sign = 1;
	while ((*str >= '\t' && *str <= '\r') || *str == ' ')
		str++;
	if (*str == '-' || *str == '+')
		if (*str++ == '-')
			sign *= -1;
	while (ft_isdigit(*str))
		result = (result * 10) + (*str++ - '0');
	return (result * sign);
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

int	ft_isalpha(int ch)
{
	if ((ch >= 'a' && ch <= 'z')
		|| (ch >= 'A' && ch <= 'Z'))
		return (1);
	else
		return (0);
}

int	ft_isascii(int var)
{
	if (var >= 0 && var <= 127)
		return (1);
	else
		return (0);
}

int	ft_isdigit(int dig)
{
	if (dig >= '0' && dig <= '9')
		return (1);
	else
		return (0);
}

int	ft_isprint(int var)
{
	if (var >= ' ' && var <= '~')
		return (1);
	else
		return (0);
}

static int	ft_intlen(long int num)
{
	int	cnt;

	cnt = 0;
	if (num <= 0)
	{
		cnt++;
		num = -num;
	}
	while (num > 0)
	{
		cnt++;
		num /= 10;
	}
	return (cnt);
}

char	*ft_itoa(int num)
{
	long int	absnum;
	int			numlen;
	char		*str;

	absnum = num;
	numlen = ft_intlen(absnum);
	str = ft_calloc(numlen + 1, sizeof(char));
	if (!str)
		return (NULL);
	if (absnum < 0)
		absnum = -absnum;
	while (numlen > 0)
	{
		str[--numlen] = absnum % 10 + '0';
		absnum /= 10;
	}
	if (num < 0)
		str[0] = '-';
	return (str);
}

void	*ft_memchr(const void *str, int ch, size_t numby)
{
	if (numby == '\0')
		return (NULL);
	while (numby--)
	{
		if (*(char *)str == (char)ch)
			return ((char *)str);
		str++;
	}
	return (NULL);
}

int	ft_memcmp(const void *str0, const void *str1, size_t numby)
{
	long int	cnt;

	cnt = -1;
	if (numby == 0)
		return (0);
	while (++cnt < (long int)numby)
		if (*(unsigned char *)(str0 + cnt) != *(unsigned char *)(str1 + cnt))
			return (*(unsigned char *)(str0 + cnt) -
			*(unsigned char *)(str1 + cnt));
	return (0);
}

void	*ft_memcpy(void *dest, const void *src, size_t numby)
{
	long int	cnt;

	cnt = -1;
	if (!dest && !src)
		return (NULL);
	while (++cnt < (long int)numby)
		*(char *)(dest + cnt) = *(char *)(src + cnt);
	return (dest);
}

void	*ft_memmove(void *dest, const void *src, size_t numby)
{
	if (!dest && !src)
		return (NULL);
	if (dest < src)
		return (ft_memcpy(dest, src, numby));
	while (numby--)
		*(char *)(dest + numby) = *(char *)(src + numby);
	return (dest);
}

void	*ft_memset(void *buffer, int value, size_t len)
{
	while (len--)
		*(unsigned char *)(buffer + len) = value;
	return (buffer);
}

void	ft_putchar_fd(char ch, int fd)
{
	write(fd, &ch, 1);
}

void	ft_putendl_fd(char *str, int fd)
{
	write(fd, str, ft_strlen(str));
	write(fd, "\n", 1);
}

void	ft_putnbr_fd(int num, int fd)
{
	long int	nwnum;

	nwnum = num;
	if (nwnum < 0)
	{
		nwnum *= -1;
		ft_putchar_fd('-', fd);
	}
	if (nwnum > 9)
		ft_putnbr_fd(nwnum / 10, fd);
	ft_putchar_fd(nwnum % 10 + '0', fd);
}

void	ft_putstr_fd(char *str, int fd)
{
	write(fd, str, ft_strlen(str));
}

static void	mksplit(char const *str, char ch, size_t cnt, char **substr)
{
	char	*str1;
	size_t	strini;
	size_t	strlen;

	while (str[cnt])
	{
		if (str[cnt] && str[cnt] != ch)
		{
			strini = cnt;
			while (str[cnt] && str[cnt] != ch)
				cnt++;
			strlen = (cnt - strini) + 1;
			str1 = malloc(sizeof(char) * strlen);
			ft_strlcpy(str1, &str[strini], strlen);
			*(char **)(substr++) = str1;
		}
		if (str[cnt] && str[cnt] == ch)
			while (str[cnt] && str[cnt] == ch)
				cnt++;
	}
	substr = NULL;
}

static size_t	cntwords(char const *str, char ch)
{
	size_t	words;

	words = 0;
	while (*str)
	{
		if (*str && *str != ch)
		{
			while (*str && *str != ch)
				str++;
			words++;
		}
		if (*str && *str == ch)
			while (*str && *str == ch)
				str++;
	}
	return (words + 1);
}

char	**ft_split(char const *str, char ch)
{
	size_t	numstrmk;
	char	**strsplit;

	if (!str)
		return (NULL);
	numstrmk = cntwords(str, ch);
	strsplit = ft_calloc((numstrmk), sizeof(char *));
	if (!strsplit)
		return (NULL);
	mksplit(str, ch, 0, strsplit);
	return (strsplit);
}

char	*ft_strchr(const char *str, int ch)
{
	while (*str && *str != (char)ch)
		str++;
	if ((char)ch == *str)
		return ((char *)str);
	return (0);
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

void	ft_striteri(char *str, void (*ftn)(unsigned int, char*))
{
	int		cnt;

	cnt = -1;
	while (str[++cnt])
		ftn(cnt, &str[cnt]);
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

size_t	ft_strlcat(char *dest, const char *src, size_t destsz)
{
	size_t	lenx;
	size_t	len0;
	size_t	len1;

	lenx = 0;
	len0 = ft_strlen(dest);
	len1 = ft_strlen(src);
	if (destsz <= len0)
		return (len1 + destsz);
	while (src[lenx] && (len0 + 1) < destsz)
		dest[len0++] = src[lenx++];
	dest[len0] = '\0';
	return (ft_strlen(dest) + ft_strlen(&src[lenx]));
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

char	*ft_strmapi(char const *str, char (*ftn)(unsigned int, char))
{
	int		cnt;
	char	*result;

	if (!str || !ftn)
		return (NULL);
	cnt = -1;
	result = ft_calloc(ft_strlen(str) + 1, sizeof(char));
	if (!result)
		return (NULL);
	while (str[++cnt])
		result[cnt] = ftn(cnt, str[cnt]);
	result[cnt] = '\0';
	return (result);
}

int	ft_strncmp(const char *str0, const char *str1, size_t numby)
{
	size_t	cnt;

	cnt = 0;
	if (numby == 0)
		return (0);
	while (str0[cnt] && (str0[cnt] == str1[cnt]) && cnt < (numby - 1))
		cnt++;
	return ((unsigned char)str0[cnt] - (unsigned char)str1[cnt]);
}

char	*ft_strnstr(const char *big, const char *ltl, size_t lench)
{
	size_t	lenb;
	size_t	lenl;

	lenb = 0;
	lenl = ft_strlen(ltl);
	if (lenl == 0)
		return ((char *)big);
	while (*big && lenb <= lench)
	{
		if (lench - lenb++ >= lenl && !ft_strncmp(big, ltl, lenl))
			return ((char *)big);
		big++;
	}
	return (0);
}

char	*ft_strrchr(const char *str, int ch)
{
	int	cnt;

	cnt = ft_strlen(str);
	while (cnt != 0 && str[cnt] != (char)ch)
		cnt--;
	if (str[cnt] == (char)ch)
		return ((char *)str + cnt);
	return (NULL);
}

char	*ft_strtrim(char const *str0, char const *set)
{
	char	*nwstr;
	size_t	cnt;

	if (!str0 || !set)
		return (NULL);
	while (*str0 && ft_strchr(set, *str0))
		str0++;
	cnt = ft_strlen(str0) + 1;
	while (cnt && ft_strchr(set, str0[cnt - 1]))
		cnt--;
	nwstr = (char *) malloc((cnt + 1) * sizeof(char));
	if (!nwstr)
		return (NULL);
	ft_strlcpy(nwstr, str0, cnt + 1);
	return (nwstr);
}

char	*ft_substr(char const *str, unsigned int start, size_t len)
{
	char	*nwstr;
	size_t	lenstr;

	if (!str)
		return (NULL);
	lenstr = ft_strlen(str);
	if (start >= lenstr)
		return (ft_strdup(""));
	if (lenstr - start >= len)
		nwstr = malloc((len + 1) * sizeof(char));
	else
		nwstr = malloc((lenstr - start + 1) * sizeof(char));
	if (nwstr)
	{
		if (len > lenstr + 1)
			len = lenstr + 1;
		ft_strlcpy(nwstr, (str + start), (len + 1));
	}
	else
		return (NULL);
	return (nwstr);
}

int	ft_tolower(int ch)
{
	if (ch >= 'A' && ch <= 'Z')
		ch += 32;
	return (ch);
}

int	ft_toupper(int ch)
{
	if (ch >= 'a' && ch <= 'z')
		ch -= 32;
	return (ch);
}

char	*lms_strjoin_free(char *str1, char *str2)
{
	char	*joined;

	joined = ft_strjoin(str1, str2);
	free(str1);
	return (joined);
}

void	lms_putchar(char ch)
{
	write(1, &ch, 1);
}

int	lms_putenv(char ***env, char *str)
{
	char	*equal_sign;
	char	*name;
	char	*value;

	if (!env || !str)
		return (-1);
	equal_sign = ft_strchr(str, '=');
	if (!equal_sign)
		return (-1);
	*equal_sign = '\0';
	name = str;
	value = equal_sign + 1;
	return (lms_setenv(env, name, value, 1));
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

void	*lms_realloc(void *ptr, size_t nwsize)
{
	void	*nwptr;
	size_t	oldsz;

	if (!ptr)
		return (malloc(nwsize));
	oldsz = malloc_usable_size(ptr);
	if (nwsize == 0)
	{
		free(ptr);
		return (NULL);
	}
	nwptr = malloc(nwsize);
	if (!nwptr)
	{
		free(ptr);
		return (NULL);
	}
	if (oldsz < nwsize)
		ft_memcpy(nwptr, ptr, oldsz);
	else
		ft_memcpy(nwptr, ptr, nwsize);
	free(ptr);
	return (nwptr);
}

static int	create_env_string(const char *name,
							const char *value, char **result)
{
	char	*env_in;

	if (!name || !value || !result)
		return (-1);
	env_in = ft_strjoin(name, "=");
	if (!env_in)
		return (-1);
	*result = ft_strjoin(env_in, value);
	free(env_in);
	if (!(*result))
		return (-1);
	return (0);
}

static int	update_existing_env(char **env, const char *name,
							char *env_in, int overwrite)
{
	int	index;

	index = 0;
	while (env[index])
	{
		if (ft_strncmp(env[index], name, ft_strlen(name)) == 0
			&& env[index][ft_strlen(name)] == '=')
		{
			if (overwrite)
			{
				free(env[index]);
				env[index] = env_in;
			}
			else
				free(env_in);
			return (1);
		}
		index++;
	}
	return (0);
}

static int	add_new_env(char ***env, char *env_in, int env_size)
{
	*env = lms_realloc(*env, sizeof(char *) * (env_size + 2));
	if (!(*env))
	{
		free(env_in);
		return (-1);
	}
	(*env)[env_size] = env_in;
	(*env)[env_size + 1] = NULL;
	return (0);
}

int	lms_setenv(char ***env, const char *name, const char *value, int overwrite)
{
	char	*env_in;
	int		env_size;

	if (create_env_string(name, value, &env_in) == -1)
		return (-1);
	if (!env || !*env)
	{
		free(env_in);
		return (-1);
	}
	if (update_existing_env(*env, name, env_in, overwrite))
		return (0);
	env_size = 0;
	while ((*env)[env_size])
		env_size++;
	return (add_new_env(env, env_in, env_size));
}

int	lms_strcmp(const char *s1, const char *s2)
{
	return (ft_strncmp(s1, s2, 1000000));
}

char	*lms_strncpy(char *dest, const char *src, size_t n)
{
	size_t	cnt;

	cnt = 0;
	while (cnt < n && src[cnt] != '\0')
	{
		dest[cnt] = src[cnt];
		cnt++;
	}
	while (cnt < n)
	{
		dest[cnt] = '\0';
		cnt++;
	}
	return (dest);
}

char	*lms_strndup(const char *str, size_t n)
{
	char	*dup;

	dup = (char *)malloc(n + 1);
	if (!dup)
		return (NULL);
	lms_strncpy(dup, str, n);
	dup[n] = '\0';
	return (dup);
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

static int	find_env_var(char **env, const char *name)
{
	int	index;

	index = 0;
	while (env[index])
	{
		if (ft_strncmp(env[index], name, ft_strlen(name)) == 0
			&& env[index][ft_strlen(name)] == '=')
			return (index);
		index++;
	}
	return (-1);
}

static void	shift_env_vars(char **env, int start_index)
{
	while (env[start_index + 1])
	{
		env[start_index] = env[start_index + 1];
		start_index++;
	}
	env[start_index] = NULL;
}

int	lms_unsetenv(char ***env, const char *name)
{
	int	index;

	if (!env || !name || !(*env))
		return (-1);
	index = find_env_var(*env, name);
	if (index == -1)
		return (0);
	free((*env)[index]);
	shift_env_vars(*env, index);
	return (0);
}

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


char	**dup_env(char **envp)
{
	char	**nwenv;
	int		cnt;
	int		index;

	cnt = 0;
	while (envp[cnt])
		cnt++;
	nwenv = ft_calloc(cnt + 1, sizeof(char *));
	if (!nwenv)
		return (NULL);
	index = -1;
	while (++index < cnt)
	{
		nwenv[index] = ft_strdup(envp[index]);
		if (!nwenv[index])
		{
			while (--index >= 0)
				free(nwenv[index]);
			free(nwenv);
			return (NULL);
		}
	}
	return (nwenv);
}

int	main(int argc, char **argv, char **envp)
{
	t_minishell	shell;

	(void)argc;
	(void)argv;
	shell.env = dup_env(envp);
	shell.prompt = NULL;
	shell.exit_stt = 0;
	welcome();
	while (1)
	{
		ms_prompt(&shell);
	}
	return (0);
}
