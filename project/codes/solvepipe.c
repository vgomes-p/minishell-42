/* < libms > */
int	lms_isnum(const char *str)
{
	if (!str || !*str)
		return (0);
	if (*str == '-' || *str == '+')
		str++;
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (0);
		str++;
	}
	return (1);
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

void	*lms_realloc(void *ptr, size_t oldsz, size_t nwsize)
{
	void	*nwptr;

	if (!ptr)
		return (malloc(nwsize));
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

int	lms_strcmp(const char *s1, const char *s2)
{
	return (ft_strncmp(s1, s2, 1000000));
}

char	*lms_strjoin_char(char const *str0, char ch)
{
	char	*result;
	size_t	len;
	size_t	pos;

	if (!str0)
		return (NULL);
	len = ft_strlen(str0);
	result = (char *)malloc(len + 2);
	if (!result)
		return (NULL);
	pos = 0;
	while (str0[pos])
	{
		result[pos] = str0[pos];
		pos++;
	}
	result[pos] = ch;
	result[pos + 1] = '\0';
	return (result);
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

/* <minishell.h> */
#ifndef MINISHELL_H
# define MINISHELL_H

# include <fcntl.h>
# include <errno.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <signal.h>
# include <curses.h>
# include <termcap.h>
# include <stdbool.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <sys/types.h>
# include "libft/libft.h"
# include "libms/libms.h"
# include <readline/history.h>
# include <readline/readline.h>

# ifndef SEP
#  define SEP -1
# endif

# define RESET		"\001\033[0m\002"
# define RED		"\001\033[1;31m\002"
# define GREEN		"\001\033[1;32m\002"
# define YELLOW		"\001\033[1;33m\002"
# define PINK		"\001\033[1;35m\002"
# define CYAN		"\001\033[1;36m\002"
# define ORANGE		"\001\033[1;38;5;214m\002"
# define RERED		"\001\033[1;7;31m\002"
# define REYELLOW	"\001\033[1;7;33m\002"
# define REGREEN	"\001\033[1;7;32m\002"
# define REPINK		"\001\033[1;7;35m\002"
# define RECYAN		"\001\033[1;7;36m\002"
# define REORANGE	"\001\033[1;7;38;5;214m\002"
# define REWHITE	"\001\033[1;7;97m\002"

typedef enum e_token_tp
{
	CMD,
	ARG,
	PIPE,
	APPEND,
	HEREDOC,
	REDIR_IN,
	REDIR_OUT,
	REDIR_APPEND,
	SYNTAX_ERROR,
}	t_token_tp;

typedef struct s_token
{
	char			*value;
	t_token_tp		type;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

typedef struct s_exec
{
	t_token	*temp;
	char	**cmd;
	int		**fd;
	int		stts;
	pid_t	*pid;
	int		nbr_pros;
	t_token	*tokens_head;
}	t_exec;

typedef struct s_expand
{
	char	**hold_str;
	int		exec;
	int		start;
	int		end;
	int		quotes;
	int		exec_n;
	int		i;
}	t_expand;

typedef struct s_cmd_exec
{
	char	**cmd;
	int		**fd;
	int		pos;
	t_token	*cmd_tokens;
}	t_cmd_exec;

typedef struct s_minishell
{
	int		pid;
	char	**env;
	char	*prompt;
	size_t	env_size;
	int		exit_stt;
	int		term_width;
	int		error_code;
	int		term_height;
	char	*error_message;
	t_token	*tokens;
}	t_minishell;

extern t_minishell	*g_shell;

#endif

/* <minishell.c> */
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
		return ;
	pos = 0;
	while (fd[pos])
	{
		free(fd[pos]);
		pos++;
	}
	free(fd);
}

void	free_matrix(char ***matrix)
{
	int	pos;

	if (!matrix || !*matrix)
		return ;
	pos = 0;
	while ((*matrix)[pos])
	{
		free((*matrix)[pos]);
		(*matrix)[pos] = NULL;
		pos++;
	}
	free(*matrix);
	*matrix = NULL;
}

void	free_env(char **env)
{
	int	pos;

	if (!env)
		return ;
	pos = 0;
	while (env[pos])
	{
		free(env[pos]);
		pos++;
	}
	free(env);
}

static int	dup_env_str(char **nwenv, char **envp, size_t cnt)
{
	size_t	pos;

	pos = 0;
	while (pos < cnt)
	{
		nwenv[pos] = ft_strdup(envp[pos]);
		if (!nwenv[pos])
		{
			while (--pos > 0)
				free(nwenv[--pos]);
			free(nwenv);
			return (0);
		}
		pos++;
	}
	nwenv[cnt] = NULL;
	return (1);
}

char	**dup_env(char **envp, size_t *envsz)
{
	char	**nwenv;
	size_t	cnt;

	if (!envp || !envsz)
		return (NULL);
	cnt = 0;
	while (envp[cnt])
		cnt++;
	*envsz = cnt;
	nwenv = ft_calloc(cnt + 1, sizeof(char *));
	if (!nwenv)
		return (NULL);
	if (!dup_env_str(nwenv, envp, cnt))
		return (NULL);
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

void	interactive_signal_handler(int sig)
{
	if (sig == SIGINT)
	{
		lms_putchar('\n');
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
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
return (ft_substr(input, start, *pos - start));
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

static bool	is_pipe_valid(t_token *current, bool cmd_before)
{
	if (!cmd_before)
	{
		printf(RED "Syntax error: unexpected token '|'\n" RESET);
		return (false);
	}
	if (!current->next || (current->next->type != CMD
			&& current->next->type != ARG))
	{
		printf(RED "Syntax error: unexpected token '|'\n" RESET);
		return (false);
	}
	return (true);
}

static bool	is_redir_valid(t_token *current)
{
	if (!current->next || current->next->type != ARG)
	{
		printf(RED "Syntax error: '%s' operator without args.\n" RESET,
			current->value);
		return (false);
	}
	return (true);
}

static bool	process_token(t_token **current, bool *cmd_before)
{
	if ((*current)->type == CMD || (*current)->type == ARG)
		*cmd_before = true;
	else if ((*current)->type == PIPE)
	{
		if (!is_pipe_valid(*current, *cmd_before))
			return (false);
		*cmd_before = false;
	}
	else if ((*current)->type == REDIR_OUT || (*current)->type == REDIR_IN
		|| (*current)->type == REDIR_APPEND || (*current)->type == HEREDOC)
	{
		if (!is_redir_valid(*current))
			return (false);
		*current = (*current)->next;
	}
	return (true);
}

static bool	check_first_token(t_token *tokens)
{
	if (!tokens)
		return (true);
	if (tokens->type == PIPE)
	{
		printf(RED "Syntax error: unexpected token '|'\n" RESET);
		return (false);
	}
	return (true);
}

bool	valid_syntax(t_token *tokens)
{
	t_token	*current;
	bool	cmd_before;

	if (!check_first_token(tokens))
		return (false);
	cmd_before = false;
	current = tokens;
	while (current)
	{
		if (!process_token(&current, &cmd_before))
			return (false);
		current = current->next;
	}
	if (!cmd_before)
	{
		printf(RED "Syntax error: unexpected token '|'\n" RESET);
		return (false);
	}
	return (true);
}

static char	*extract_var_name(char *str, int *ind0)
{
	char	*var_start;
	char	*var_end;
	char	*var_name;

	var_start = &str[*ind0];
	if (str[*ind0] == '?')
	{
		(*ind0)++;
		var_name = ft_strdup("?");
	}
	else
	{
		while (str[*ind0] && (ft_isalnum(str[*ind0]) || str[*ind0] == '_'))
			(*ind0)++;
		var_end = &str[*ind0];
		var_name = ft_substr(var_start, 0, var_end - var_start);
	}
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

static char	*expand_inside(t_minishell *shell, char *str)
{
	char	*result;
	int		index[2];

	index[0] = 0;
	index[1] = 0;
	result = ft_calloc(ft_strlen(str) + 1024, sizeof(char));
	if (!result)
		return (str);
	while (str[index[0]])
	{
		if (str[index[0]] == '$' && str[index[0] + 1]
			&& str[index[0] + 1] != ' ')
			handle_var(shell, str, result, index);
		else
			result[index[1]++] = str[index[0]++];
	}
	free(str);
	return (result);
}

char	*expand_var(t_minishell *shell, char *token)
{
	char	*result;
	char	*inside;

	if (token[0] == '\'' && token[ft_strlen(token) - 1] == '\'')
	{
		result = ft_substr(token, 1, ft_strlen(token) - 2);
		free(token);
		return (result);
	}
	else if (token[0] == '"' && token[ft_strlen(token) - 1] == '"')
	{
		inside = ft_substr(token, 1, ft_strlen(token) - 2);
		free(token);
		result = expand_inside(shell, inside);
		free(inside);
		return (result);
	}
	else
	{
		result = expand_inside(shell, token);
		free(token);
		return (result);
	}
}

static void	handle_redir_in(t_minishell *shell, t_token *current)
{
	int	fd_in;

	fd_in = open(current->next->value, O_RDONLY);
	if (fd_in < 0)
	{
		file_errmsg(shell, current->next->value);
		exit(1);
	}
	dup2(fd_in, STDIN_FILENO);
	close(fd_in);
}

static void	handle_redir_out(t_minishell *shell, t_token *current, int append)
{
	int	fd_out;
	int	flags;

	flags = O_WRONLY | O_CREAT;
	if (append)
		flags |= O_APPEND;
	else
		flags |= O_TRUNC;
	fd_out = open(current->next->value, flags, 0644);
	if (fd_out < 0)
	{
		file_errmsg(shell, current->next->value);
		exit(1);
	}
	dup2(fd_out, STDOUT_FILENO);
	close(fd_out);
}

static void	pros_redirs(t_minishell *shell, t_token *current)
{
	if (current->type == REDIR_IN && current->next)
		handle_redir_in(shell, current);
	else if (current->type == REDIR_OUT && current->next)
		handle_redir_out(shell, current, 0);
	else if (current->type == REDIR_APPEND && current->next)
		handle_redir_out(shell, current, 1);
	else if (current->type == HEREDOC && current->next)
		process_heredoc(shell, current);
}

void	ms_redirs(t_minishell *shell, t_token *tokens, int **fd, int pos)
{
	t_token	*current;

	current = tokens;
	while (current && current->type != PIPE)
	{
		if ((current->type == REDIR_IN || current->type == REDIR_OUT
				|| current->type == REDIR_APPEND || current->type == HEREDOC)
			&& current->next)
			pros_redirs(shell, current);
		current = current->next;
	}
	if (pos > 0)
		dup2(fd[pos - 1][0], STDIN_FILENO);
	if (fd[pos])
		dup2(fd[pos][1], STDOUT_FILENO);
}

static int	open_heredoc_file(t_minishell *shell, int mode)
{
	int	fd;

	if (mode == 0)
		fd = open("__heredoc", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else
		fd = open("__heredoc", O_RDONLY);
	if (fd < 0)
	{
		perror(RED "heredoc" RESET);
		shell->error_code = 1;
		return (-1);
	}
	return (fd);
}

static void	write_heredoc_content(int fd, char *delimiter)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (!line || lms_strcmp(line, delimiter) == 0)
		{
			free(line);
			break ;
		}
		ft_putstr_fd(line, fd);
		ft_putstr_fd("\n", fd);
		free(line);
	}
}

static int	validate_heredoc_delimiter(t_minishell *shell, t_token *token)
{
	if (!token->next || !token->next->value)
	{
		ft_putstr_fd(RED "Syntax error: heredoc missing delimiter\n" RESET, 2);
		shell->error_code = 2;
		return (0);
	}
	return (1);
}

void	process_heredoc(t_minishell *shell, t_token *token)
{
	char	*delimiter;
	int		fd;

	if (!validate_heredoc_delimiter(shell, token))
		return ;
	delimiter = token->next->value;
	fd = open_heredoc_file(shell, 0);
	if (fd < 0)
		return ;
	write_heredoc_content(fd, delimiter);
	close(fd);
	fd = open_heredoc_file(shell, 1);
	if (fd < 0)
		return ;
	dup2(fd, STDIN_FILENO);
	close(fd);
}

static int	count_args(t_token *tokens)
{
	t_token	*current;
	int		arg_count;

	arg_count = 0;
	if (!tokens)
		return (0);
	current = tokens;
	while (current)
	{
		if (current->type == CMD || current->type == ARG)
			arg_count++;
		if (is_redir(current))
			current = current->next;
		if (current)
			current = current->next;
	}
	return (arg_count);
}

static char	**allocate_args_array(int arg_count)
{
	char	**args;

	if (arg_count <= 0)
		return (NULL);
	args = malloc(sizeof(char *) * (arg_count + 1));
	return (args);
}

static int	fill_args_array(char **args, t_token *tokens, int arg_count)
{
	t_token	*current;
	int		arg_pos;

	arg_pos = 0;
	current = tokens;
	while (current && arg_pos < arg_count)
	{
		if (current->type == CMD || current->type == ARG)
		{
			args[arg_pos] = ft_strdup(current->value);
			if (!args[arg_pos])
				return (0);
			arg_pos++;
		}
		if (is_redir(current))
			current = current->next;
		if (current)
			current = current->next;
	}
	args[arg_pos] = NULL;
	return (1);
}

char	**prepare_args(t_token *tokens)
{
	char	**args;
	int		arg_count;

	if (!tokens)
		return (NULL);
	arg_count = count_args(tokens);
	args = allocate_args_array(arg_count);
	if (!args)
		return (NULL);
	if (!fill_args_array(args, tokens, arg_count))
	{
		free_matrix(&args);
		return (NULL);
	}
	return (args);
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
		free_matrix(&cmd);
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

static t_token	*handle_pipe_node(t_token **tokens, t_token *prev,
	t_token *current, t_token *cmd_start)
{
t_token	*pipe_node;

pipe_node = current;
if (prev)
prev->next = NULL;
else
cmd_start = NULL;
*tokens = current->next;
free(pipe_node->value);
free(pipe_node);
return (cmd_start);
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
return (handle_pipe_node(tokens, prev, current, cmd_start));
else
{
*tokens = NULL;
return (cmd_start);
}
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
			free_matrix(&ls);
			return (1);
		}
	}
	free_matrix(&ls);
	return (0);
}

int	is_redir(t_token *token)
{
	return (token->type == REDIR_IN || token->type == REDIR_OUT
		|| token->type == REDIR_APPEND || token->type == HEREDOC);
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
	free_matrix(&path_dir);
	path_dir = NULL;
	return (full_path);
}

static void	restore_std_fds(int stdin_backup, int stdout_backup)
{
	dup2(stdin_backup, STDIN_FILENO);
	dup2(stdout_backup, STDOUT_FILENO);
	close(stdin_backup);
	close(stdout_backup);
}

static int	handle_builtin_command(char **args, t_minishell *shell)
{
	int	ret;

	ret = 1;
	if (lms_strcmp(args[0], "cd") == 0)
	{
		ms_cd(args, shell);
		shell->exit_stt = shell->error_code;
	}
	else if (lms_strcmp(args[0], "echo") == 0)
	{
		ms_echo(args);
		shell->exit_stt = 0;
	}
	else if (lms_strcmp(args[0], "env") == 0)
	{
		ms_env(shell);
		shell->exit_stt = 0;
	}
	else if (lms_strcmp(args[0], "exit") == 0)
		ms_exit(args, shell);
	return (ret);
}

static int	handle_more_builtins(char **args, t_minishell *shell)
{
	int	ret;

	ret = 1;
	if (lms_strcmp(args[0], "pwd") == 0)
	{
		ms_pwd(shell);
		shell->exit_stt = shell->error_code;
	}
	else if (lms_strcmp(args[0], "export") == 0)
	{
		ms_export(shell, args, &shell->env);
		ret = shell->error_code;
		shell->exit_stt = ret;
	}
	else if (lms_strcmp(args[0], "unset") == 0)
	{
		ms_unset(shell, args, &shell->env);
		shell->exit_stt = shell->error_code;
	}
	else
		ret = 0;
	return (ret);
}

int	exec_builtin(t_token *tokens, t_minishell *shell, int **fd, int pos)
{
	char	**args;
	int		ret;
	int		stdin_backup;
	int		stdout_backup;

	stdin_backup = dup(STDIN_FILENO);
	stdout_backup = dup(STDOUT_FILENO);
	args = prepare_args(tokens);
	if (!args)
		return (-1);
	ms_redirs(shell, tokens, fd, pos);
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (lms_strcmp(args[0], "cd") == 0 || lms_strcmp(args[0], "echo") == 0
		|| lms_strcmp(args[0], "env") == 0 || lms_strcmp(args[0], "exit") == 0)
		ret = handle_builtin_command(args, shell);
	else
		ret = handle_more_builtins(args, shell);
	restore_std_fds(stdin_backup, stdout_backup);
	free_matrix(&args);
	return (ret);
}

static int	allocate_pipes(t_exec *exec)
{
	int	pos;

	exec->fd = ft_calloc(exec->nbr_pros, sizeof(int *));
	if (!exec->fd)
		return (0);
	pos = -1;
	while (++pos < (exec->nbr_pros - 1))
	{
		exec->fd[pos] = ft_calloc(2, sizeof(int));
		if (!exec->fd[pos])
		{
			while (--pos >= 0)
				free(exec->fd[pos]);
			free(exec->fd);
			return (0);
		}
	}
	pos = -1;
	while (++pos < exec->nbr_pros - 1)
		pipe(exec->fd[pos]);
	return (1);
}

t_exec	init_exec(t_minishell *shell, t_token *tokens)
{
	t_exec	exec;

	(void)shell;
	exec.tokens_head = tokens;
	exec.temp = tokens;
	exec.pid = NULL;
	exec.stts = 0;
	exec.nbr_pros = 1;
	exec.cmd = tokens_matrix(exec.temp);
	while (exec.temp)
	{
		if (exec.temp->type == PIPE)
			exec.nbr_pros++;
		exec.temp = exec.temp->next;
	}
	if (exec.nbr_pros <= 0)
	{
		free_matrix(&exec.cmd);
		exec.fd = NULL;
		return (exec);
	}
	if (!allocate_pipes(&exec))
		free_matrix(&exec.cmd);
	exec.temp = exec.tokens_head;
	return (exec);
}

void	cleanup_processes(t_exec *exec, t_minishell *shell, int cmd_pos)
{
	int	pros_pos;

	(void)cmd_pos;
	cls_fd(exec->fd);
	pros_pos = -1;
	while (exec->fd[++pros_pos])
		exec->fd[pros_pos] = (int *) free_ptr((char *) exec->fd[pros_pos]);
	sfree_int(exec->fd);
	exec->fd = NULL;
	pros_pos = -1;
	while (++pros_pos < exec->nbr_pros)
		waitpid(exec->pid[pros_pos], &exec->stts, 0);
	if (WIFEXITED(exec->stts))
		shell->exit_stt = WEXITSTATUS(exec->stts);
	else if (WIFSIGNALED(exec->stts))
		shell->exit_stt = 128 + WTERMSIG(exec->stts);
	free(exec->pid);
}

static int	handle_exec_type(t_minishell *shell, t_exec *exec,
									t_token *tokens_copy)
{
	int	cmd_pos;

	if (is_buildin(exec->cmd[0]))
	{
		exec_builtin(shell->tokens, shell, exec->fd, 0);
		free_matrix(&exec->cmd);
		sfree_int(exec->fd);
		free_tokens(tokens_copy);
		return (0);
	}
	cmd_pos = exec_parent(shell, exec->nbr_pros, exec->cmd, exec->fd);
	if (cmd_pos > 0)
		free_matrix(&exec->cmd);
	if (cmd_pos == 0)
	{
		free_matrix(&exec->cmd);
		sfree_int(exec->fd);
		free_tokens(tokens_copy);
		return (0);
	}
	return (cmd_pos);
}

void	exec_cmd(t_minishell *shell)
{
	int		cmd_pos;
	t_exec	exec;
	t_token	*tokens_copy;

	if (!shell->tokens || !shell->tokens->value || !*shell->tokens->value)
		return ;
	tokens_copy = cpy_token_ls(shell->tokens);
	exec = init_exec(shell, tokens_copy);
	if (!exec.fd)
	{
		free_matrix(&exec.cmd);
		free_tokens(tokens_copy);
		return ;
	}
	cmd_pos = handle_exec_type(shell, &exec, tokens_copy);
	if (cmd_pos == 0)
		return ;
	exec_child(shell, &exec, cmd_pos);
	cleanup_processes(&exec, shell, cmd_pos);
	free_matrix(&exec.cmd);
	sfree_int(exec.fd);
	free(exec.pid);
	free_tokens(tokens_copy);
}

int	exec_parent(t_minishell *shell, int nb_pros, char **cmd, int **fd)
{
	if (!ft_strncmp(cmd[0], "./", 2) && is_dir(shell, cmd[0]) == 1)
		return (0);
	if (nb_pros > 1)
		return (-1);
	if (is_buildin(cmd[0]))
	{
		exec_builtin(shell->tokens, shell, fd, 0);
		sfree_int(fd);
		fd = NULL;
		return (0);
	}
	return (-1);
}

void	exec_child(t_minishell *shell, t_exec *exec, int pos)
{
	t_token		*cmd_tokens;
	t_cmd_exec	cmd_exec;

	exec->pid = ft_calloc(exec->nbr_pros, sizeof(pid_t));
	if (!exec->pid)
		return ;
	pos = -1;
	while (++pos < exec->nbr_pros)
	{
		cmd_tokens = get_next_cmd(&exec->tokens_head);
		if (!cmd_tokens)
			continue ;
		exec->cmd = prepare_args(cmd_tokens);
		if (!exec->cmd)
		{
			free_tokens(cmd_tokens);
			continue ;
		}
		cmd_exec.cmd = exec->cmd;
		cmd_exec.fd = exec->fd;
		cmd_exec.pos = pos;
		cmd_exec.cmd_tokens = cmd_tokens;
		exec->pid[pos] = fork();
		if (exec->pid[pos] == 0)
			child(shell, &cmd_exec);
		free_matrix(&exec->cmd);
		free_tokens(cmd_tokens);
	}
	cls_fd(exec->fd);
}

void	child(t_minishell *shell, t_cmd_exec *exec)
{
	if (!exec->cmd || *exec->cmd == NULL)
	{
		handle_invalid_file(shell);
		clean_child_res(shell, NULL, exec->fd, shell->error_code);
	}
	ms_redirs(shell, exec->cmd_tokens, exec->fd, exec->pos);
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	cls_fd(exec->fd);
	exec_extern(exec->cmd, shell->env);
	clean_child_res(shell, exec->cmd, exec->fd, shell->error_code);
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
	signal(SIGINT, interactive_signal_handler);
	signal(SIGQUIT, SIG_IGN);
	welcome();
	while (1)
	{
		ms_prompt(&shell);
	}
	free_env(shell.env);
	return (0);
}