/* minishell.h */
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

void		free_env(char **env);
void		free_tokens(t_token *tokens);
void		sfree(char **split);
char		*free_ptr(char *ptr);
void		sfree_int(int **fd);
char		**dup_env(char **envp, size_t *envsz);
void		handle_signal(int sig);
void		welcome(void);
void		ms_prompt(t_minishell *shell);
t_token		*mktoken(char *value, t_token_tp type);
char		**ms_split_quotes(const char *input);
t_token		*create_token_list(char **split, t_token *head);
t_token		*tokening(char *input);
bool		process_quotes(const char *input, int *pos, bool *in_quotes,
				char *quote_ch);
char		**process_tokens(const char *input, char **tokens);
char		*extract_token(const char *input, int *pos);
t_token_tp	get_token_type(char *token, t_token *current, int is_first);
bool		is_quotes(char ch);
bool		is_operator(char *str);
void		cleanup_tokens(char **tokens, int token_cnt);
int			count_tokens(t_token *tokens);
char		*clean_token(const char *str, int len);
char		**tokens_matrix(t_token *token);
t_token		*cpy_token_ls(t_token *tokens);
void		addtoken_ls(t_token *list, t_token *new_token);
int			parser(t_token **head, char *str);
bool		valid_syntax(t_token *tokens);
char		*expand_var(char *token, t_minishell *shell);
int			find_envar(const char *var, char **envp);
void		update_envar(const char *var, int index0, char ***envp);
int			valid_name(const char *var);
void		export_err(const char *arg);
void		ms_echo(char **args);
void		ms_pwd(t_minishell *shell);
void		ms_env(t_minishell *shell);
void		ms_cd(char **args, t_minishell *shell);
void		ms_exit(char **args, t_minishell *shell);
void		ms_unset(t_minishell *shell, char **args, char ***envp);
void		ms_export(t_minishell *shell, char **args, char ***envp);
char		*get_full_path(char *cmd, char **path_dir);
char		*find_exec_path(char *cmd, char **envp);
t_exec		init_exec(t_minishell *shell);
int			exec_parent(t_minishell *shell, int nb_pros, char **cmd, int **fd);
void		exec_child(t_minishell *shell, t_exec *exec, int pos);
void		cleanup_processes(t_exec *exec, t_minishell *shell, int cmd_pos);
void		exec_cmd(t_minishell *shell);
int			exec_builtin(t_token *tokens, t_minishell *shell);
int			is_buildin(char *token);
char		**prepare_args(t_token *tokens);
int			is_dir(t_minishell *shell, char *cmd);
void		cls_fd(int **fd);
void		exec_extern(char **cmd, char **envp);
void		clean_child_res(t_minishell *shell, char **cmd, int **fd, int code);
void		file_errmsg(t_minishell *shell, char *cmd);
void		handle_invalid_file(t_minishell *shell);
void		child(t_minishell *shell, char **cmd, int **fd, int pos);
t_token		*get_next_cmd(t_token **tokens);
void		handle_heredoc(t_token *token);
void		handle_redirects(t_token *token);

#endif

/* main */
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

/* free_all_0 */
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

/* utils */
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
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
	else if (sig == SIGQUIT)
	{
	}
}

/* prompt.c */
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
	shell->tokens = tokening(input);
	if (!shell->tokens)
	{
		ft_putstr_fd(RED "Error: Tokenination has failed\n" RESET, 2);
		free(input);
		return ;
	}
	if (!valid_syntax(shell->tokens))
	{
		ft_putstr_fd(RED "Syntax error\n" RESET, 2);
		free_tokens(shell->tokens);
		shell->tokens = NULL;
		free(input);
		return ;
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

/* token */
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
	char	*expanded_input;

	expanded_input = expand_var(input, g_shell);
	if (!expanded_input)
		return (NULL);
	split = ms_split_quotes(expanded_input);
	free(expanded_input);
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

/* token_utils_0 */
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

/* token_utils_1 */
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

/* token_utils_2 */
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

/* parse */
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

/* parse_utils_0 */
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

/* expand */
static char	*expand_exit_status(t_minishell *shell, int *pos)
{
	char	*var_value;

	var_value = ft_itoa(shell->exit_stt);
	*pos += 2;
	return (var_value);
}

static char	*extract_var_name(char *token, int pos)
{
	char	*var_name;
	char	*space_ptr;

	space_ptr = ft_strchr(token + pos, ' ');
	if (!space_ptr)
		var_name = ft_strdup(token + pos + 1);
	else
		var_name = ft_substr(token, pos + 1, space_ptr - (token + pos + 1));
	return (var_name);
}

static char	*expand_regular_var(char *token, int *pos, t_minishell *shell)
{
	char	*var_name;
	char	*var_value;
	int		index;

	var_name = extract_var_name(token, *pos);
	if (!var_name)
		return (NULL);
	index = find_envar(var_name, shell->env);
	if (index != -1)
		var_value = ft_strdup(ft_strchr(shell->env[index], '=') + 1);
	else
		var_value = ft_strdup("");
	*pos += ft_strlen(var_name) + 1;
	free(var_name);
	return (var_value);
}

static char	*handle_dollar_var(char *token, int *pos, t_minishell *shell)
{
	char	*var_value;

	if (token[*pos + 1] == '?')
		var_value = expand_exit_status(shell, pos);
	else
		var_value = expand_regular_var(token, pos, shell);
	return (var_value);
}

char	*expand_var(char *token, t_minishell *shell)
{
	char	*result;
	char	*var_value;
	int		pos;

	result = ft_strdup("");
	if (!result)
		return (NULL);
	pos = 0;
	while (token[pos])
	{
		if (token[pos] == '$' && (ft_isalnum(token[pos + 1]) || 
			token[pos + 1] == '?'))
		{
			var_value = handle_dollar_var(token, &pos, shell);
			result = lms_strjoin_free(result, var_value);
			free(var_value);
		}
		else
		{
			result = lms_strjoin_char(result, token[pos]);
			pos++;
		}
	}
	return (result);
}

/* bi_utils */
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

static int	copy_existing_env(char **nwenv, char **envp, int envsz)
{
	int	index1;

	index1 = -1;
	while (++index1 < envsz)
	{
		nwenv[index1] = ft_strdup(envp[index1]);
		if (!nwenv[index1])
		{
			while (--index1 >= 0)
				free(nwenv[index1]);
			free(nwenv);
			return (0);
		}
	}
	return (1);
}

static int	add_new_envar(const char *var, char ***envp, int envsz)
{
	char	**nwenv;
	int		index1;

	nwenv = ft_calloc(envsz + 2, sizeof(char *));
	if (!nwenv)
		return (0);
	if (!copy_existing_env(nwenv, *envp, envsz))
		return (0);
	nwenv[envsz] = ft_strdup(var);
	if (!nwenv[envsz])
	{
		while (--envsz >= 0)
			free(nwenv[envsz]);
		free(nwenv);
		return (0);
	}
	index1 = 0;
	while (index1 > envsz)
	{
		free((*envp)[index1]);
		index1++;
	}
	free(*envp);
	*envp = nwenv;
	return (1);
}

void	update_envar(const char *var, int index0, char ***envp)
{
	int		envsz;
	int		index1;
	char	**old_env;

	envsz = 0;
	while (*envp && (*envp)[envsz])
		envsz++;
	if (index0 < envsz)
	{
		free((*envp)[index0]);
		(*envp)[index0] = ft_strdup(var);
		return ;
	}
	old_env = *envp;
	if (!add_new_envar(var, envp, envsz))
		return ;
	index1 = -1;
	while (++index1 < envsz)
		free(old_env[index1]);
	free(old_env);
}

int	valid_name(const char *var)
{
	int	index;

	index = 0;
	if (!var || var[0] == '=' || ft_isdigit(var[0]))
		return (0);
	while (var[index] && var[index] != '=')
	{
		if (var[index] != '_' && !ft_isalnum(var[index]))
			return (0);
		index++;
	}
	return (1);
}

/* bi_utils1 */
void	export_err(const char *arg)
{
	ft_putstr_fd(RED "export: " ORANGE "\"", STDERR_FILENO);
	ft_putstr_fd((char *)arg, STDERR_FILENO);
	ft_putstr_fd("\"" RED " not a valid indentifier\n" RESET, STDERR_FILENO);
}

/* echo */
void	ms_echo(char **args)
{
	int	curr_arg;
	int	nwline;

	curr_arg = 1;
	nwline = 1;
	while (args[curr_arg] && lms_strcmp(args[curr_arg], "-n") == 0)
	{
		nwline = 0;
		curr_arg++;
	}
	while (args[curr_arg])
	{
		lms_putstr(args[curr_arg]);
		if (args[curr_arg + 1])
			lms_putstr(" ");
		curr_arg++;
	}
	if (nwline)
		lms_putstr("\n");
}

/* pwd */
void	ms_pwd(t_minishell *shell)
{
	char	*cwd;
	int		pwd_index;
	char	*pwd_env;

	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		ft_putstr_fd(RED "pwd: error" RESET, 2);
		return ;
	}
	pwd_env = ft_strjoin("PWD=", cwd);
	if (!pwd_env)
	{
		free(cwd);
		return ;
	}
	ft_putstr_fd(cwd, STDOUT_FILENO);
	ft_putstr_fd("\n", STDOUT_FILENO);
	pwd_index = find_envar("PWD", shell->env);
	update_envar(pwd_env, pwd_index, &shell->env);
	free(pwd_env);
	free(cwd);
}

/* ms_env */
void	ms_env(t_minishell *shell)
{
	int	curr_arg;

	curr_arg = 0;
	while (shell->env && shell->env[curr_arg])
	{
		ft_putendl_fd(shell->env[curr_arg], STDOUT_FILENO);
		curr_arg++;
	}
}

/* cd */
static char	*get_new_pwd(char *oldpwd)
{
	char	*nwpwd;

	nwpwd = getcwd(NULL, 0);
	if (!nwpwd)
	{
		perror(RED "cd: getcwd" RESET);
		free(oldpwd);
		return (NULL);
	}
	return (nwpwd);
}

static int	update_oldpwd(char *oldpwd, t_minishell *shell)
{
	int		index_oldpwd;
	char	*oldpwd_var;

	index_oldpwd = find_envar("OLDPWD", shell->env);
	oldpwd_var = ft_strjoin("OLDPWD=", oldpwd);
	if (!oldpwd_var)
		return (0);
	update_envar(oldpwd_var, index_oldpwd, &shell->env);
	free(oldpwd_var);
	return (1);
}

static void	update_pwd(char *oldpwd, t_minishell *shell)
{
	char	*nwpwd;
	int		pwd_index;
	char	*pwd_var;

	nwpwd = get_new_pwd(oldpwd);
	if (!nwpwd)
		return ;
	if (!update_oldpwd(oldpwd, shell))
	{
		free(nwpwd);
		free(oldpwd);
		return ;
	}
	pwd_index = find_envar("PWD", shell->env);
	pwd_var = ft_strjoin("PWD=", nwpwd);
	if (!pwd_var)
	{
		free(nwpwd);
		free(oldpwd);
		return ;
	}
	update_envar(pwd_var, pwd_index, &shell->env);
	free(pwd_var);
	free(nwpwd);
	free(oldpwd);
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
		perror(RED "cd" RESET);
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

/* exit */
static int	validate_exit_args(char **args, t_minishell *shell)
{
	if (args[1] && args[2])
	{
		ft_putstr_fd(RED "exit: too many arguments\n" RESET, 2);
		shell->exit_stt = 1;
		return (0);
	}
	if (args[1] && !lms_isnum(args[1]))
	{
		ft_putstr_fd(RED "exit: the argument " ORANGE "\"", 2);
		ft_putstr_fd(args[1], 2);
		ft_putstr_fd("\"" RED " is not a valid integer\n", 2);
		shell->exit_stt = 2;
		return (0);
	}
	return (1);
}

void	ms_exit(char **args, t_minishell *shell)
{
	int	stat;

	stat = 0;
	if (!validate_exit_args(args, shell))
		return ;
	if (args[1])
		stat = ft_atoi(args[1]);
	shell->exit_stt = stat;
	ft_putstr_fd(RECYAN "\n\n\nSee you soon, goodbye!\n\n\n" RESET, 1);
	free(shell->prompt);
	free_env(shell->env);
	rl_clear_history();
	exit(stat);
}

/* unset */
static void	rmvar(char *var, char ***envp)
{
	size_t	index;
	char	*tempvar;

	index = 0;
	if (!var || !envp || !*envp)
		return ;
	tempvar = ft_strjoin (var, "=");
	if (!tempvar)
		return ;
	while ((*envp)[index] && ft_strncmp((*envp)[index],
			tempvar, ft_strlen(tempvar)))
		index++;
	if ((*envp)[index])
	{
		free((*envp)[index]);
		while ((*envp)[index])
		{
			(*envp)[index] = (*envp)[index + 1];
			index++;
		}
		(*envp)[index] = NULL;
	}
	free(tempvar);
}

static void	unset_err(const char *arg)
{
	ft_putstr_fd(ORANGE "unset: " YELLOW "\"", STDERR_FILENO);
	ft_putstr_fd((char *)arg, STDERR_FILENO);
	ft_putstr_fd("\"" ORANGE " not found\n" RESET, STDERR_FILENO);
}

static void	unset_usage(void)
{
	ft_putstr_fd(YELLOW "usage: unser <var name>\n" RESET, STDERR_FILENO);
}

static int	validvar(const char *var, char ***envp)
{
	int		varlen;
	char	*var_eq;
	int		index;

	if (!var || !envp || !*envp)
		return (0);
	varlen = ft_strlen(var);
	var_eq = ft_strjoin(var, "=");
	if (!var_eq)
		return (0);
	index = 0;
	while ((*envp)[index])
	{
		if (ft_strncmp((*envp)[index], var_eq, varlen + 1) == 0)
		{
			free(var_eq);
			return (1);
		}
		index++;
	}
	free(var_eq);
	return (0);
}

void	ms_unset(t_minishell *shell, char **args, char ***envp)
{
	if (!args[1])
	{
		unset_usage();
		shell->error_code = 1;
		return ;
	}
	if (!envp || !*envp)
	{
		shell->error_code = 1;
		return ;
	}
	while (*(++args))
	{
		if (validvar(*args, envp))
		{
			rmvar(*args, envp);
		}
		else
		{
			unset_err(*args);
			shell->error_code = 1;
		}
	}
	shell->error_code = 0;
}

/* export */
void	ms_export(t_minishell *shell, char **args, char ***envp)
{
	int	index0;
	int	index1;

	index0 = 1;
	if (!args[1])
	{
		ms_env(shell);
		return ;
	}
	while (args[index0])
	{
		if (valid_name(args[index0]))
		{
			index1 = find_envar(args[index0], *envp);
			update_envar(args[index0], index1, envp);
			shell->error_code = 0;
		}
		else
		{
			export_err(args[index0]);
			shell->error_code = 42;
		}
		index0++;
	}
}

/*  cmd_path */
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

/* exec_buildins */
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

/* exec_child.c */
static void	process_redirections(t_token *current)
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

	process_redirections(exec->temp);
	if (!allocate_pid_memory(exec))
		return ;
	current_tokens = shell->tokens;
	process_commands(shell, exec, &current_tokens);
	(void)pos; /* Silence unused parameter warning */
}

/* exec_externs */
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

static void	process_redirections(t_token *current)
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

int	exec_parent(t_minishell *shell, int nb_pros, char **cmd, int **fd)
{
	t_token	*redir_tokens;

	redir_tokens = shell->tokens;
	process_redirections(redir_tokens);
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

/* exec_utils_0 */
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

/* exec_utils_1 */
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

/* exec_utils_2 */
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

/* heredoc */
void	handle_heredoc(t_token *token)
{
	int		fd;
	char	*line;
	char	*delim;

	delim = token->next->value;
	fd = open("__heredoc", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		perror("minishell");
		exit(1);
	}
	while (1)
	{
		line = readline("> ");
		if (!line || lms_strcmp(line, delim) == 0)
			break ;
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
	close(fd);
	fd = open("__heredoc", O_RDONLY);
	dup2(fd, STDIN_FILENO);
	close(fd);
}

/* redirect */
static int	open_input_file(char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		perror("minishell");
		exit(1);
	}
	return (fd);
}

static int	open_output_file(char *filename)
{
	int	fd;

	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0664);
	if (fd == -1)
	{
		perror("minishell");
		exit(1);
	}
	return (fd);
}

static int	open_append_file(char *filename)
{
	int	fd;

	fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0664);
	if (fd == -1)
	{
		perror("minishell");
		exit(1);
	}
	return (fd);
}

static void	redirect_and_close(int fd, int target_fd)
{
	dup2(fd, target_fd);
	close(fd);
}

void	handle_redirects(t_token *token)
{
	int	fd;

	if (token->type == REDIR_IN)
	{
		fd = open_input_file(token->next->value);
		redirect_and_close(fd, STDIN_FILENO);
	}
	else if (token->type == REDIR_OUT)
	{
		fd = open_output_file(token->next->value);
		redirect_and_close(fd, STDOUT_FILENO);
	}
	else if (token->type == REDIR_APPEND)
	{
		fd = open_append_file(token->next->value);
		redirect_and_close(fd, STDOUT_FILENO);
	}
}